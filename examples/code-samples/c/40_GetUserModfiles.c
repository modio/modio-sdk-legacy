#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onGetUserModfiles(void *object, ModioResponse response, ModioModfile *modfiles, u32 modfiles_size)
{
  bool *wait = object;
  printf("On modfiles get response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Listing modfiles\n");
    printf("================\n");
    for (u32 i = 0; i < modfiles_size; i++)
    {
      printf("Modfile[%i]\n", i);
      printf("Id:\t%i\n", modfiles[i].id);
      printf("Version:\t%s\n", modfiles[i].version);
      printf("Changelog:\t%s\n", modfiles[i].changelog);
      printf("Metadata blob:\t%s\n", modfiles[i].metadata_blob);
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

  printf("Getting modfiles...\n");

  // Now we finished setting up the filters we are ready to request the mods
  modioGetUserModfiles(&wait, filter, &onGetUserModfiles);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
