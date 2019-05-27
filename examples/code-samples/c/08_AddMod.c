#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onAddMod(void *object, ModioResponse response, ModioMod mod)
{
  bool *wait = object;
  printf("Add mod response code: %i\n", response.code);

  if (response.code == 201)
  {
    printf("Mod added!\n");
    printf("Mod id: %i\n", mod.id);
    printf("Mod name: %s\n", mod.name);
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  if (!modioIsLoggedIn())
  {
    printf("You are not logged in, please login before creating a mod.\n");
    return 0;
  }

  bool wait = true;

  // The Mod Creator helps setting up the fields before creating a Mod
  ModioModCreator mod_creator;
  modioInitModCreator(&mod_creator);
  modioSetModCreatorLogoPath(&mod_creator, "../ModExample/logo.png");
  modioSetModCreatorName(&mod_creator, "Example Mod Test");
  modioSetModCreatorHomepageURL(&mod_creator, "http://www.webpage.com");
  modioSetModCreatorSummary(&mod_creator, "Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples.");
  modioAddModCreatorTag(&mod_creator, "Easy");
  modioAddModCreatorTag(&mod_creator, "Medium");
  modioSetModCreatorDescription(&mod_creator, "This mod description was added via the SDK examples. This mod description was added via the SDK examples.");
  modioSetModCreatorMetadataBlob(&mod_creator, "Optional metadata");
  modioSetModCreatorMaturityOption(&mod_creator, MODIO_MATURITY_VIOLENCE | MODIO_MATURITY_ALCOHOL);

  printf("Adding mod...\n");

  // Now we can create the new mod. Remember, this mod wont have a Modfile right away, you should be adding one after the mod was created successfully
  modioAddMod(&wait, mod_creator, &onAddMod);

  modioFreeModCreator(&mod_creator);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
