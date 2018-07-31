#include "modio_c.h"

void onGetModfiles(void *object, ModioResponse response, ModioModfile modfiles[], u32 modfiles_size)
{
  bool *wait = object;
  printf("On get mod events response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Listing events\n");
    printf("==============\n");
    for (u32 i = 0; i < modfiles_size; i++)
    {
      printf("Id:\t%i\n", modfiles[i].id);
      printf("Version:\t%s\n", modfiles[i].version);
      printf("Changelog:\t%s\n\n", modfiles[i].changelog);
    }
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Just like mods and other schemas, modfiles can be filtered using the Filter Creator
  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter, 3);

  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Getting mod events...\n");

  // Now we finished setting up the filters we are ready to request the modfiles
  modioGetModfiles(&wait, mod_id, filter, &onGetModfiles);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
