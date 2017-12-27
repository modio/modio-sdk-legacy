#include "schemas.h"

void onModfileEdited(void* object, ModioResponse response, ModioModfile modfile)
{
  bool* wait = object;
  printf("Edit Mod response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Mod edited successfully!\n");
  }
  *wait = false;
}

void onModsGet(void* object, ModioResponse response, ModioMod* mods, u32 mods_size)
{
  bool* wait = object;
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200 && mods_size > 0)
  {
    ModioMod mod = mods[0];
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);

    printf("Editing modfile...\n");

    // The Modfile Handler helps setting up the fields that will be edited
    // Notice that the version field and modfile zip can't be edited, you should be uploading another modfile instead
    ModioModfileHandler modfile_handler;
    modioInitModfileHandler(&modfile_handler);
    modioSetModfileActive(&modfile_handler,false);
    modioSetModfileChangelog(&modfile_handler,(char*)"Stuff was changed on this mod via the examples.");

    modioEditModfile(wait, mod.id, mod.modfile.id, modfile_handler, &onModfileEdited);
  }else
  {
    *wait = false;
  }
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  // Let's start by requesting a single mod

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,1);

  printf("Getting mods...\n");
  modioGetMods(&wait, filter, &onModsGet);

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
