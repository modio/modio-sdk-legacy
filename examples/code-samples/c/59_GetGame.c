#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onGetGame(void* object, ModioResponse response, ModioGame game)
{
  bool* wait = object;
  printf("On mod get response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Id:\t%i\n", game.id);
    printf("Name:\t%s\n", game.name);
    printf("Summary:\t%s\n", game.summary);
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, false, false, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // To retreive a game we simply need it's id
  printf("Please enter the game id: \n");
  u32 game_id;
  scanf("%i", &game_id);

  printf("Getting game...\n");
  modioGetGame(&wait, game_id, &onGetGame);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
