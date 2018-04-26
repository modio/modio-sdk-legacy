#include "modio_c.h"

bool wait = true;

void onModfileAdded(u32 response_code, u32 mod_id)
{
  printf("Add Modfile Response: %i\n", response_code);
  if (response_code == 201)
  {
    printf("Modfile added!\n");
  }
  wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b");

  if (!modioIsLoggedIn())
  {
    printf("You are not logged in, please login before creating a mod.\n");
    return 0;
  }

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

  // Just like the download listener, we can register a function to be called every time a mod us uploaded
  modioSetUploadListener(&onModfileAdded);

  // To start the modfile upload, we provide the mod id and the modfile creator object
  modioAddModfile(mod_id, modfile_creator);
  modioFreeModfileCreator(&modfile_creator);
  
  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
