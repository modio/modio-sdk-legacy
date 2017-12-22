#include "schemas.h"

bool mods_get_finished = false;
bool get_tags_finished = false;

ModioMod* global_mod;

void onGetTags(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size)
{
  bool* wait = object;
  printf("Get Tags response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Listing tags:\n");
    for(int i=0; i < tags_array_size; i++)
    {
      printf("%s\n", tags_array[i].name);
    }
  }
  *wait = false;
}

void onModsGet(void* object, ModioResponse response, ModioMod* mods, int mods_size)
{
  bool* wait = object;
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200 && mods_size > 0)
  {
    ModioMod mod = mods[0];
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);

    printf("Getting tags...\n");

    modioGetTags(wait, mod.id, &onGetTags);
  }else
  {
    *wait = false;
  }
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  ModioFilterHandler filter;
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
