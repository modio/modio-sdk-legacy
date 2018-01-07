#include "schemas.h"

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

void onModsGet(void* object, ModioResponse response, ModioMod* mods, u32 mods_size)
{
  bool* wait = object;
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200 && mods_size > 0)
  {
    ModioMod mod = mods[0];
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);

    // The Modfile Creator helps us setting up the modfile fields and the mod directory that will be zipped and uploaded
    ModioModfileCreator modfile_creator;
    modioInitModfileCreator(&modfile_creator);
    modioSetModfileCreatorPath(&modfile_creator, "../ModExample/modfile/");
    modioSetModfileCreatorVersion(&modfile_creator, "v1.1.0");
    modioSetModfileCreatorChangelog(&modfile_creator, "This is a change log, this is a changelog , this is a changelog , this is a changelog , this is a changelog , this is a changelog, this is a changelog , this is a changelog , this is a changelog");
    modioSetModfileCreatorActive(&modfile_creator, true);

    modioAddModfile(wait, mod.id, modfile_creator, &onModfileAdded);

    modioFreeModfileCreator(&modfile_creator);
  }else
  {
    *wait = false;
  }
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  {
    ModioListNode oa;
  }

  if(!modioIsLoggedIn())
  {
    printf("You are not logged in, please login before creating a mod.\n");
    return 0;
  }

  bool wait = true;

  // Let's start by requesting a single mod

  ModioFilterCreator filter;
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
