#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onModUnsubscribed(void *object, ModioResponse response)
{
  bool *wait = object;
  printf("Subscribe to Mod Response code: %i\n", response.code);

  if (response.code == 204)
  {
    printf("Unsubscribed from mod!\n");
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

  printf("Unsubscribing to mod...\n");
  modioUnsubscribeFromMod(&wait, mod_id, &onModUnsubscribed);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
