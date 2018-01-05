#include "schemas.h"

void onModEdited(void* object, ModioResponse response, ModioMod mod)
{
  bool* wait = object;
  printf("Mod Edit response: %i\n", response.code);
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

    // The Mod Handler helps setting up the fields that will be updated
    ModioModHandler mod_handler;
    modioInitModHandler(&mod_handler);
    modioSetLogoPath(&mod_handler, (char*)"../ModExample/logo.png");
    modioSetName(&mod_handler, (char*)"Update Example");
    modioSetHomepage(&mod_handler, (char*)"http://www.updated.com");
    modioSetSummary(&mod_handler, (char*)"Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples.");
    modioAddTag(&mod_handler, (char*)"Easy");
    modioSetDescription(&mod_handler, (char*)"This mod description was updated via the SDK examples. This mod description was updated via the SDK examples.");
    modioSetMetadataBlob(&mod_handler, (char*)"Optional updated metadata");

    modioEditMod(wait, mod.id, mod_handler, &onModEdited);
  }else
  {
    *wait = false;
  }
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,1);

  printf("Getting mods...\n");

  // Let's start by requesting a single mod

  modioGetMods(&wait, filter, &onModsGet);

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
