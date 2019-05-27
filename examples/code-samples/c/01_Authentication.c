#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void onExchange(void *object, ModioResponse response)
{
  bool *wait = object;
  if (response.code == 200)
  {
    printf("Code exchanged!\n");
  }
  else
  {
    printf("Error exchanging code\n");
  }
  *wait = false;
}

void onEmailRequest(void *object, ModioResponse response)
{
  bool *wait = object;
  if (response.code == 200)
  {
    printf("Email request successful\n");
  }
  else
  {
    printf("Error sending code\n");
  }

  char security_code[6];
  printf("Please enter the 5 digit security code: \n");
  fgets(security_code, 6, stdin);
  security_code[strcspn(security_code, "\n")] = 0;
  printf("Sending code... \n");

  // Finish the auth process by entering the security code
  modioEmailExchange(wait, security_code, &onExchange);
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Check to see if we have a cookie and are already logged in
  if (!modioIsLoggedIn())
  {
    char email[50];
    printf("Enter your email: \n");
    fgets(email, 50, stdin);
    email[strcspn(email, "\n")] = 0;
    printf("Sending email to %s\n", email);
    printf("Sending email... \n");

    // Auth works by sending an email with a code. Lets trigger that now
    modioEmailRequest(&wait, email, &onEmailRequest);
    while (wait)
    {
      modioProcess();
    }
  }
  else
  {
    printf("You are already logged in. Do you want to logout? (y/n)\n");
    char user_option[2];
    fgets(user_option, 2, stdin);
    user_option[strcspn(user_option, "\n")] = 0;
    if (strcmp(user_option, "y") == 0)
    {
      modioLogout();
    }
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
