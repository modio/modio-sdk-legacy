#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onOculusAuth(void *object, ModioResponse response)
{
  bool *wait = object;
  if (response.code == 200)
  {
    printf("Successful Oculus authentication\n");
  }
  else
  {
    printf("Error while authenticating to Oculus: %i\n", response.code);
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Auth works by providing the data given by the Oculus SDK
  char *nonce = "GALAXY NONCE PROOF HERE";
  u32 user_id = 123123;
  char *access_token = "GALAXY AUTH TOKEN HERE";
  char *email = NULL; // Optional email param
  u32 date_expires = 0; // Optional expiration date param, 0 will be ignored
  modioOculusAuth(&wait, nonce, user_id, access_token, email, date_expires, &onOculusAuth);
  
  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
