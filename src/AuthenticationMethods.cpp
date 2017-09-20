#include "AuthenticationMethods.h"

namespace modworks
{
  map< int,function<void(int)> > email_request_callbacks;
  map< int,function<void(int)> > email_exchange_callbacks;

  void onEmailRequested(int call_number, int response_code, json response)
  {
    email_request_callbacks[call_number](response_code);
    email_request_callbacks.erase(call_number);
  }

  void emailRequest(string email, function< void(int response_code) > callback)
  {
    map<string, string> data;
    data["api_key"] = api_key;
    data["email"] = email;

    int call_number = getCallCount();
    advanceCallCount();

    email_request_callbacks[call_number] = callback;

    std::thread email_request_thread(post, call_number, "https://api.mod.works/oauth/emailrequest?shhh=secret", data, &onEmailRequested);
    email_request_thread.detach();
  }

  void onEmailExchanged(int call_number, int response_code, json response)
  {
    if(response_code == 200)
    {
      access_token = response["access_token"];
      json token_json;
      token_json["access_token"] = response["access_token"];
      std::ofstream out(getModworksDirectory() + "token.json");
      out<<setw(4)<<token_json<<endl;
      out.close();
    }

    email_exchange_callbacks[call_number](response_code);
    email_exchange_callbacks.erase(call_number);
  }

  void emailExchange(string security_code, function< void(int) > callback)
  {
    map<string, string> data;
    data["api_key"] = api_key;
    data["security_code"] = security_code;

    int call_number = getCallCount();
    advanceCallCount();

    email_exchange_callbacks[call_number] = callback;

    std::thread email_exchage_thread(post, call_number, "https://api.mod.works/oauth/emailexchange?shhh=secret",data, &onEmailExchanged);
    email_exchage_thread.detach();
  }

  bool isLoggedIn()
  {
    return access_token!="";
  }

  void logout()
  {
    access_token = "";

    json empty_json;
    std::ofstream out(getModworksDirectory() + "token.json");
    out<<setw(4)<<empty_json<<endl;
    out.close();
  }
}
