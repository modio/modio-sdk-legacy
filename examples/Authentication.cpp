#include "ModIOSDK.h"
#include "Filter.h"

#ifdef _WIN32
#define WINDOWS
#endif
#ifdef _WIN64
#define WINDOWS
#endif

bool email_request_finished = false;
bool email_exchange_finished = false;

void onEmailRequest(int response_code, char* message)
{
  if(response_code == 200)
  {
    cout<<"Code sent!"<<endl;
  }else
  {
    cout<<"Error sending code"<<endl;
  }
  email_request_finished = true;
}

void onExchange(int response_code, char* message)
{
  if(response_code == 200)
  {
    cout<<"Code exchanged!"<<endl;
  }else
  {
    cout<<"Error exchanging code"<<endl;
  }
  email_exchange_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  if(!modioIsLoggedIn())
  {
    string email;
    cout<<"Enter your email: "<<endl;
    cin>>email;
    modioEmailRequest((char*)email.c_str(),&onEmailRequest);
    while(!email_request_finished);
    string security_code;
    cout<<"Please enter the 5 digit security code: ";
    cin>>security_code;
    cout<<"Sending code"<<endl;
    modioEmailExchange((char*)security_code.c_str(),&onExchange);
    while(!email_exchange_finished);
  }else
  {
    cout<<"You are already logged in. Do you want to logout? (y/n)"<<endl;
    string user_option;
    cin>>user_option;
    if(user_option == "y")
    {
      modioLogout();
    }
  }

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
