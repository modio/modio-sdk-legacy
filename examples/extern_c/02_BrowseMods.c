#include "schemas.h"

void onModsGet(void* object, ModioResponse response, ModioMod* mods, int mods_size)
{
  bool* wait = object;
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

    printf("\nPagination:\n");
    printf("Result count: %i\n",response.result_count);
    printf("Result limit: %i\n",response.result_limit);
    printf("Result Offset: %i\n",response.result_offset);
  }
  *wait = false;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,3);

  printf("Getting mods...\n");
  modioGetMods(&wait,filter, &onModsGet);

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
