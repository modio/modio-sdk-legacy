#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onLinkExternalAccount(void *object, ModioResponse response)
{
  bool *wait = object;
  if (response.code == 200)
  {
    printf("Account linked successfully\n");
  }
  else
  {
    printf("Error linking accounts\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Link mod.io accounts with service accounts such as Galaxy and Steam 
  u32 service = MODIO_SERVICE_STEAM;
  char* service_id = "USER SERVICE ID HERE";
  char* email = "USER EMAIL HERE";
  modioLinkExternalAccount(&wait, MODIO_SERVICE_STEAM, service_id, email, &onLinkExternalAccount);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
