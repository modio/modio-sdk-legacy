#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onAddModRating(void *object, ModioResponse response)
{
  bool *wait = object;
  printf("Set user mod vote code: %i\n", response.code);

  if (response.code == 201)
  {
    printf("Mod rated!\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  // Let's start by requesting a single mod
  printf("Enter 1 for a positive rating or 0 for a negative one: \n");
  u32 rating;
  scanf("%i", &rating);

  printf("Rating mod...\n");
  modioAddModRating(&wait, mod_id, rating, &onAddModRating);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
