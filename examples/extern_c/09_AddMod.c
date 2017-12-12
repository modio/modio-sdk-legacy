#include "schemas.h"

bool add_mod_finished = false;

void onModAdded(void* object, ModioResponse response, ModioMod mod)
{
  printf("Add Mod Response code: %i\n", response.code);

  if(response.code == 201)
  {
    printf("Mod added!\n");
    printf("Mod id: %i\n", mod.id);
    printf("Mod name: %s\n", mod.name);
  }

  add_mod_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  if(!modioIsLoggedIn())
  {
    printf("You are not logged in, please login before creating a mod.\n");
    return 0;
  }

  ModioModHandler mod_handler;
  modioInitModHandler(&mod_handler);
  //Required fields
  modioSetLogoPath(&mod_handler, (char*)"ModExample/logo.png");
  modioSetName(&mod_handler, (char*)"Example Mod Test");
  modioSetHomepage(&mod_handler, (char*)"http://www.webpage.com");
  modioSetSummary(&mod_handler, (char*)"Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples.");
  modioAddTag(&mod_handler, (char*)"Easy");
  modioAddTag(&mod_handler, (char*)"Medium");
  //Optional fields
  modioSetPrice(&mod_handler, 1.99);
  modioSetStock(&mod_handler, 25);
  modioSetDescription(&mod_handler, (char*)"This mod description was added via the SDK examples. This mod description was added via the SDK examples.");
  modioSetMetadata(&mod_handler, (char*)"Optional metadata");
  //setNameid(&mod_handler, "my-example-mod"); //Name id must be unique
  //setModfile(&mod_handler, int modfile); //Modfile should exist

  printf("Adding mod...\n");

  modioAddMod(NULL, mod_handler, &onModAdded);

  while(!add_mod_finished)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
