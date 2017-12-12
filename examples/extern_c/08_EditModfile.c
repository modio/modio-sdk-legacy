#include "schemas.h"

bool mods_get_finished = false;
bool modfile_edited = false;

ModioModfile* global_modfile = NULL;

void onModfileEdited(void* object, ModioResponse response, ModioModfile modfile)
{
  printf("Edit Mod response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Mod edited successfully!\n");
  }
  modfile_edited = true;
}

void onModsGet(void* object, ModioResponse response, ModioMod* mods, int mods_size)
{
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200)
  {
    printf("Listing mod\n");
    printf("============\n");
    for(int i=0;i<(int)mods_size;i++)
    {
      printf("Mod[%i]\n",i);
      printf("Id:\t%i\n",mods[i].id);
      printf("Name:\t%s\n",mods[i].name);
      global_modfile = &(mods[i].modfile);
    }
  }
  mods_get_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,1);

  printf("Getting mods...\n");
  modioGetMods(NULL, filter, &onModsGet);

  while(!mods_get_finished)
  {
    modioProcess();
  }

  printf("Editing modfile...\n");

  ModioModfileHandler modfile_handler;
  modioInitModfileHandler(&modfile_handler);
  modioSetModfileActive(&modfile_handler,false);
  modioSetModfileChangelog(&modfile_handler,(char*)"Stuff was changed on this mod via the examples.");

  modioEditModfile(NULL, global_modfile->mod_id, global_modfile->id, modfile_handler, &onModfileEdited);

  while(!modfile_edited)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
