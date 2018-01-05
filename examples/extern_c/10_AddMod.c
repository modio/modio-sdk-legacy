#include "schemas.h"

void onModAdded(void* object, ModioResponse response, ModioMod mod)
{
  bool* wait = object;
  printf("Add Mod Response code: %i\n", response.code);

  if(response.code == 201)
  {
    printf("Mod added!\n");
    printf("Mod id: %i\n", mod.id);
    printf("Mod name: %s\n", mod.name);
  }
  *wait = false;
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

  // The Mod Handler helps setting up the fields before creating a Mod
  ModioModHandler mod_handler;
  modioInitModHandler(&mod_handler);
  modioSetLogoPath(&mod_handler, (char*)"../ModExample/logo.png");
  modioSetName(&mod_handler, (char*)"Example Mod Test");
  modioSetHomepage(&mod_handler, (char*)"http://www.webpage.com");
  modioSetSummary(&mod_handler, (char*)"Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples.");
  modioAddTag(&mod_handler, (char*)"Easy");
  modioAddTag(&mod_handler, (char*)"Medium");
  modioSetDescription(&mod_handler, (char*)"This mod description was added via the SDK examples. This mod description was added via the SDK examples.");
  modioSetMetadataBlob(&mod_handler, (char*)"Optional metadata");

  printf("Adding mod...\n");

  // Now we can create the new mod. Remember, this mod wont have a Modfile right away, you should be adding one after the mod was created successfully
  modioAddMod(&wait, mod_handler, &onModAdded);

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
