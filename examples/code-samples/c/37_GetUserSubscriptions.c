#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onGetUserSubscriptions(void *object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  bool *wait = object;
  printf("On mod get response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Listing mod\n");
    printf("============\n");
    for (u32 i = 0; i < mods_size; i++)
    {
      printf("Mod[%i]\n", i);
      printf("Id:\t%i\n", mods[i].id);
      printf("Name:\t%s\n", mods[i].name);
    }
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Before requesting mods, let's define the query filters
  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter, 3);

  printf("Getting mods...\n");

  // Now we finished setting up the filters we are ready to request the mods
  modioGetUserSubscriptions(&wait, filter, &onGetUserSubscriptions);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
