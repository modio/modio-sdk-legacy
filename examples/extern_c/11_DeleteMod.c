#include "schemas.h"

bool mods_get_finished = false;
bool mod_deleted_finished = false;

ModioMod* global_mod;

void onModDeleted(void* object, ModioResponse response, int mod_id)
{
  printf("Mod Delete response: %i\n", response.code);
  if(response.code == 204)
  {
    printf("Mod deleted downloaded successfully!\n");
  }
  mod_deleted_finished = true;
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
  modioGetMods(NULL, &filter, &onModsGet);

  while(!mods_get_finished)
  {
    modioProcess();
  }

  printf("Deleting mod...\n");

  modioDeleteMod(NULL, global_mod->id, &onModDeleted);

  while(!mod_deleted_finished)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
