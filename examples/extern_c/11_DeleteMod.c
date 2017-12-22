#include "schemas.h"

bool mods_get_finished = false;
bool mod_deleted_finished = false;

ModioMod* global_mod;

void onModDeleted(void* object, ModioResponse response, int mod_id)
{
  bool* wait = object;
  printf("Mod Delete response: %i\n", response.code);
  if(response.code == 204)
  {
    printf("Mod deleted downloaded successfully!\n");
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

    printf("Deleting mod...\n");

    modioDeleteMod(wait, mod.id, &onModDeleted);
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
