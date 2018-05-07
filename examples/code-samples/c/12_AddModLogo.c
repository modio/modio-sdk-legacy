#include "modio_c.h"

void onAddModLogo(void *object, ModioResponse response)
{
  bool *wait = object;
  printf("Edit mod logo response: %i\n", response.code);
  if (response.code == 201)
  {
    printf("Image downloaded successfully!\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Getting mod...\n");
  modioAddModLogo(&wait, mod_id, (char *)"../ModExample/logo.png", &onAddModLogo);
  
  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
