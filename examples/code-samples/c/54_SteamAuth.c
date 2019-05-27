#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onSteamAuth(void *object, ModioResponse response)
{
  bool *wait = object;
  if (response.code == 200)
  {
    printf("Steam auth successful\n");
  }
  else
  {
    printf("Error authenticating to steam\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Auth works by providing the params given by the Steam SDK
  unsigned char* rgubTicket = "BINARY DATA HERE";
  u32 cubTicket = 0;
  modioSteamAuth(&wait, rgubTicket, cubTicket, &onSteamAuth);
  
  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
