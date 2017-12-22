#include "schemas.h"

void onModsGet(void* object, ModioResponse response, ModioMod* mods, int mods_size)
{
  bool* wait = object;
  printf("On mod get response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Success!\n");
  }else
  {
    printf("Error message: %s\n",response.error.message);
    if(response.error.errors_array_size > 0)
    {
      printf("Errors:\n");
      for(int i=0; i<response.error.errors_array_size; i++)
      {
        printf("%s\n",response.error.errors_array[i]);
      }
    }
  }
  *wait = false;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,-1);
  modioSetFilterOffset(&filter, -1);

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
