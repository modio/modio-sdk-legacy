#include "modio_c.h"

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
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  // The Modfile Creator helps us setting up the modfile fields and the mod directory that will be zipped and uploaded
  ModioModfileCreator modfile_creator;
  modioInitModfileCreator(&modfile_creator);
  modioSetModfileCreatorPath(&modfile_creator, "../ModExample/modfile/");
  modioSetModfileCreatorVersion(&modfile_creator, "v1.1.0");
  modioSetModfileCreatorChangelog(&modfile_creator, "This is a change log, this is a changelog , this is a changelog , this is a changelog , this is a changelog , this is a changelog, this is a changelog , this is a changelog , this is a changelog");
  modioSetModfileCreatorActive(&modfile_creator, true);

  modioAddModfile(&wait, mod_id, modfile_creator, &onModfileAdded);

  modioFreeModfileCreator(&modfile_creator);
  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
