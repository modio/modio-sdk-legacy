#include "modio_c.h"

void onModDeleted(void *object, ModioResponse response)
{
  bool *wait = object;
  printf("Mod delete response: %i\n", response.code);
  if (response.code == 204)
  {
    printf("Mod deleted successfully!\n");
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

  // We delete a mod providing the Mod id
  printf("Deleting mod...\n");
  modioDeleteMod(&wait, mod_id, &onModDeleted);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
