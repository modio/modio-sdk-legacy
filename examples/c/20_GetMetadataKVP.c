#include "modio_c.h"

void onGetMetadataKVP(void* object, ModioResponse response, ModioMetadataKVP* metadata_kvp_array, u32 metadata_kvp_array_size)
{
  bool* wait = object;
  printf("Get MetadataKVP response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Listing metadata kvp:\n");
    for(u32 i=0; i < metadata_kvp_array_size; i++)
    {
      printf("%s:%s\n", metadata_kvp_array[i].metakey, metadata_kvp_array[i].metavalue);
    }
  }
  *wait = false;
}

void onModGet(void* object, ModioResponse response, ModioMod mod)
{
  bool* wait = object;
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200)
  {
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);

    printf("Getting metadata kvp...\n");

    // We request the list of metadata key value pairs by providing the Mod's id
    modioGetMetadataKVP(wait, mod.id, &onGetMetadataKVP);
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
