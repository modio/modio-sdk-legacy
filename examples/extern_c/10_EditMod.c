#include "schemas.h"

bool mods_get_finished = false;
bool mods_edited_finished = false;

ModioMod* global_mod = NULL;

void onModEdited(void* object, ModioResponse response, ModioMod mod)
{
  printf("Mod Edit response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Mod edited successfully!\n");
  }
  mods_edited_finished = true;
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

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,1);

  printf("Getting mods...\n");
  modioGetMods(NULL, filter, &onModsGet);

  while(!mods_get_finished)
  {
    modioProcess();
  }

  ModioModHandler mod_handler;
  modioInitModHandler(&mod_handler);
  //Required fields
  modioSetLogoPath(&mod_handler, (char*)"ModExample/logo.png");
  modioSetName(&mod_handler, (char*)"Update Example");
  modioSetHomepage(&mod_handler, (char*)"http://www.updated.com");
  modioSetSummary(&mod_handler, (char*)"Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples.");
  modioAddTag(&mod_handler, (char*)"Easy");
  //Optional fields
  modioSetPrice(&mod_handler, 2.99);
  //setStock(mod_handler, 50);//The developer should allow mods to control mod supply and scarcity
  modioSetDescription(&mod_handler, (char*)"This mod description was updated via the SDK examples. This mod description was updated via the SDK examples.");
  modioSetMetadata(&mod_handler, (char*)"Optional updated metadata");
  //setNameid(&mod_handler, "my-example-mod"); //Name id must be unique
  //setModfile(&mod_handler, int modfile); //Modfile should exist

  modioEditMod(NULL, global_mod->id, mod_handler, &onModEdited);

  while(!mods_edited_finished)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
