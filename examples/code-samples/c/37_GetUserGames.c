#include "modio_c.h"

void onGetUserGames(void *object, ModioResponse response, ModioGame *games, u32 games_size)
{
  bool *wait = object;
  printf("On game get response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Listing games\n");
    printf("============\n");
    for (u32 i = 0; i < games_size; i++)
    {
      printf("Game[%i]\n", i);
      printf("Id:\t%i\n", games[i].id);
      printf("Name:\t%s\n", games[i].name);
    }
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Before requesting mods, let's define the query filters
  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter, 3);

  printf("Getting mods...\n");

  // Now we finished setting up the filters we are ready to request the mods
  modioGetUserGames(&wait, filter, &onGetUserGames);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
