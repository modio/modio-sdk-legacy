#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  // Use modioGetCurrentUser in conjuction with the modioIsLoggedIn to check the current user cache
  if(modioIsLoggedIn())
  {
      printf("Logged in as %s\n", modioGetCurrentUser().username);
  }else
  {
    printf("You are not logged in.\n");    
  }
  

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
