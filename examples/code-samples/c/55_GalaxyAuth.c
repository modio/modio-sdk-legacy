#include "modio_c.h"

void onGalaxyAuth(void *object, ModioResponse response)
{
  bool *wait = object;
  if (response.code == 200)
  {
    printf("GOG auth successful\n");
  }
  else
  {
    printf("Error authenticating to GOG\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Auth works by sending an email with a code. Lets trigger that now
  modioGalaxyAuth(&wait, "", &onGalaxyAuth);
  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
