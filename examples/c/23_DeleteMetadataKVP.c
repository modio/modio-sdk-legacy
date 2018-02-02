#include "modio_c.h"

void onDeleteMetadataKVP(void* object, ModioResponse response)
{
  bool* wait = object;
  printf("Delete Metdata KVP response: %i\n", response.code);
  if(response.code == 201)
  {
    printf("Metadata KVP deleted successfully!\n");
  }
  *wait = false;
}

void onModGet(void* object, ModioResponse response, ModioMod mod)
{
  bool* wait = object;
  printf("On mod get response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);

    printf("Deleting metadata kvp...\n");

    char** metadata_kvp_array = (char**) malloc(1);
    metadata_kvp_array[0] = (char*) malloc(50);
    strcpy(metadata_kvp_array[0], "pistol-dmg:800\0");

    // We delete metadata key value pairs from a mod by providing a string with the same format we added it
    // Keep in mind the value can be omited, in that case all the values with the key provided will be deleted
    modioDeleteMetadataKVP(wait, mod.id, (char**)metadata_kvp_array, 1, &onDeleteMetadataKVP);
  }else
  {
    *wait = false;
  }
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Getting mod...\n");
  modioGetMod(&wait, mod_id, &onModGet);

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
