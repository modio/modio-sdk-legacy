#include "schemas.h"

void onDeleteTags(void* object, ModioResponse response, u32 mod_id)
{
  bool* wait = object;
  printf("Delete Tags response: %i\n", response.code);
  if(response.code == 201)
  {
    printf("Tag deleted successfully!\n");
  }
  *wait = false;
}

void onModsGet(void* object, ModioResponse response, ModioMod* mods, u32 mods_size)
{
  bool* wait = object;
  printf("On mod get response: %i\n", response.code);
  if(response.code == 200 && mods_size > 0)
  {
    ModioMod mod = mods[0];
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);

    printf("Adding tags...\n");

    char** tags_array = (char**) malloc(1);
    tags_array[0] = (char*) malloc(50);
    strcpy(tags_array[0], "Hard\0");

    // We delete tags by providing the selected Mod id and the tag names
    modioDeleteTags(wait, mod.id, (char**)tags_array, 1, &onDeleteTags);
  }else
  {
    *wait = false;
  }
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

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
