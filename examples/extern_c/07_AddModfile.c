#include "schemas.h"

bool mods_get_finished = false;
bool add_modfile_finished = false;

ModioMod* global_mod = NULL;

void onModfileAdded(void* object, ModioResponse response, ModioModfile modfile)
{
  bool* wait = object;
  printf("Add Modfile Response: %i\n", response.code);
  if(response.code == 201)
  {
    printf("Modfile added!\n");
  }
  *wait = false;
}

void onModsGet(void* object, ModioResponse response, ModioMod* mods, int mods_size)
{
  bool* wait = object;
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200 && mods_size > 0)
  {
    ModioMod mod = mods[0];
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);

    ModioModfileHandler modfile_handler;
    modioInitModfileHandler(&modfile_handler);
    //Required
    modioSetModfilePath(&modfile_handler, "ModExample/modfile/");
    modioSetModfileVersion(&modfile_handler, "v1.1.0");
    modioSetModfileChangelog(&modfile_handler, "This is a change log, this is a changelog , this is a changelog , this is a changelog , this is a changelog , this is a changelog, this is a changelog , this is a changelog , this is a changelog");
    //Optional
    modioSetModfileActive(&modfile_handler, true);

    modioAddModfile(wait, mod.id, modfile_handler, &onModfileAdded);
  }else
  {
    *wait = false;
  }
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  if(!modioIsLoggedIn())
  {
    printf("You are not logged in, please login before creating a mod.\n");
    return 0;
  }

  bool wait = true;

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
