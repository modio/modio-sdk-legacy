#include "ModIOSDK.h"

bool email_request_finished = false;
bool email_exchange_finished = false;

void onEmailRequest(int response_code, string message)
{
  if(response_code == 200)
    cout<<"Code sent!"<<endl;
  else
    cout<<"Error sending code"<<endl;

  if(message != "")
    cout<<message<<endl;

  email_request_finished = true;
}

void onExchange(int response_code, string message)
{
  if(response_code == 200)
    cout<<"Code exchanged!"<<endl;
  else
    cout<<"Error exchanging code"<<endl;

  if(message != "")
    cout<<message<<endl;

  email_exchange_finished = true;
}

int main(void)
{
  modio::init(/*game_id*/7, /*api_key*/"e91c01b8882f4affeddd56c96111977b"/*, "other_dir"*/);
  modio::setDebugMode(modio::verbose);

  if(!modio::isLoggedIn())
  {
    string email;
    cout<<"Enter your email: "<<endl;
    cin>>email;
    modio::emailRequest(email,&onEmailRequest);
    while(!email_request_finished);
    string security_code;
    cout<<"Please enter the 5 digit security code: ";
    cin>>security_code;
    cout<<"Sending code"<<endl;
    modio::emailExchange(security_code,&onExchange);
    while(!email_exchange_finished);
  }
  else
  {
    cout<<"You are already logged in do you want logout? (y/n): ";
    string answer;
    cin>>answer;
    if(answer == "y")
      modio::logout();
  }

  return 0;
}
