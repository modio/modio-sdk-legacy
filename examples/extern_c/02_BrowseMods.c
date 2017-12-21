#include "schemas.h"

bool mods_get_finished = false;

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
    }

    printf("\nCursor data:\n");
    //printf("Result count: %i\n",response.result_count);
  }

  mods_get_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,3);

  printf("Getting mods...\n");
  modioGetMods(NULL,filter, &onModsGet);

  while(!mods_get_finished)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
