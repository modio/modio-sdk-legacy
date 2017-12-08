#include "schemas.h"

bool mods_get_finished = false;
bool add_modfile_finished = false;

ModioMod* global_mod = NULL;

void onModfileAdded(void* object, ModioResponse response, ModioModfile modfile)
{
  printf("Add Modfile Response: %i\n", response.code);
  if(response.code == 201)
  {
    printf("Modfile added!\n");
  }
  add_modfile_finished = true;
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
      global_mod = &(mods[i]);
    }
  }
  mods_get_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  if(!modioIsLoggedIn())
  {
    printf("You are not logged in, please login before creating a mod.\n");
    return 0;
  }

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,1);

  printf("Getting mods...\n");
  modioGetMods(NULL, &filter, &onModsGet);

  while(!mods_get_finished)
  {
    modioProcess();
  }

  ModioModfileHandler modfile_handler;
  modioInitModfileHandler(&modfile_handler);
  //Required
  modioSetModfilePath(&modfile_handler, "ModExample/modfile/");
  modioSetModfileVersion(&modfile_handler, "v1.1.0");
  modioSetModfileChangelog(&modfile_handler, "This is a change log, this is a changelog , this is a changelog , this is a changelog , this is a changelog , this is a changelog, this is a changelog , this is a changelog , this is a changelog");
  //Optional
  modioSetModfileActive(&modfile_handler, true);

  modioAddModfile(NULL, global_mod->id, &modfile_handler, &onModfileAdded);

  while(!add_modfile_finished)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
