#include "schemas.h"

bool email_request_finished = false;
bool email_exchange_finished = false;

void onEmailRequest(void* object, ModioResponse response)
{
  if(response.code == 200)
  {
    printf("Email request successful\n");
  }else
  {
    printf("Error sending code\n");
  }
  email_request_finished = true;
}

void onExchange(void* object, ModioResponse response)
{
  if(response.code == 200)
  {
    printf("Code exchanged!\n");
  }else
  {
    printf("Error exchanging code\n");
  }
  email_exchange_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  if(!modioIsLoggedIn())
  {
    char email[50];
    printf("Enter your email: \n");
    fgets(email, 50, stdin);
    email[strcspn(email, "\n")] = 0;
    printf("Sending email to %s\n",email);
    printf("Sending email... \n");
    modioEmailRequest(NULL,(char*)email,&onEmailRequest);
    while(!email_request_finished)
    {
      modioProcess();
    }
    char security_code[6];
    printf("Please enter the 5 digit security code: \n");
    fgets(security_code, 6, stdin);
    security_code[strcspn(security_code, "\n")] = 0;
    printf("Sending code: \n");
    modioEmailExchange(NULL,(char*)security_code,&onExchange);
    while(!email_exchange_finished)
    {
      modioProcess();
    }
  }else
  {
    printf("You are already logged in. Do you want to logout? (y/n)\n");
    char user_option[2];
    fgets(user_option, 2, stdin);
    user_option[strcspn(user_option, "\n")] = 0;
    if(strcmp(user_option, "y")==0)
    {
      modioLogout();
    }
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
