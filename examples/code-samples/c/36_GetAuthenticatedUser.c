#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onGetAuthenticatedUser(void *object, ModioResponse response, ModioUser user)
{
  bool *wait = object;
  printf("On get authenticated user response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Id:\t%i\n", user.id);
    printf("Name:\t%s\n", user.username);
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  printf("Getting authenticated user...\n");
  modioGetAuthenticatedUser(&wait, &onGetAuthenticatedUser);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
