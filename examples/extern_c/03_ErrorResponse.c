#include "schemas.h"

bool mods_get_finished = false;

void onModsGet(void* object, ModioResponse response, ModioMod* mods, int mods_size)
{
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

  mods_get_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,-1);
  modioSetFilterOffset(&filter, -1);

  printf("Getting mods...\n");
  modioGetMods(NULL, filter, &onModsGet);

  while(!mods_get_finished)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
