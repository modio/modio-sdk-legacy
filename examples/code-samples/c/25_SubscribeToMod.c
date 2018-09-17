#include "modio_c.h"

void onSubscribeToMod(void *object, ModioResponse response, ModioMod mod)
{
  bool *wait = object;
  printf("Subscribe to Mod Response code: %i\n", response.code);

  if (response.code == 201)
  {
    printf("Subscribed to mod!\n");
    printf("Mod id: %i\n", mod.id);
    printf("Mod name: %s\n", mod.name);
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Subscribing to mod...\n");
  modioSubscribeToMod(&wait, mod_id, &onSubscribeToMod);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
