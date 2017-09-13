#include "Authentication.h"

namespace modworks
{
  map< int,function<void(int)> > email_request_callbacks;
  map< int,EmailExchangeParams* > email_exchange_callbacks;

  void onEmailRequested(int call_number, json response)
  {
    writeLogLine("onEmailRequested call", verbose);
    int result_code = response["code"];
    email_request_callbacks[call_number](result_code);
    email_request_callbacks.erase(call_number);
    writeLogLine("onEmailRequested finished", verbose);
  }

  void emailRequest(string email, function< void(int response) > callback)
  {
    writeLogLine("emailRequest call", verbose);
    map<string, string> data;
    data["api_key"] = api_key;
    data["email"] = email;

    int call_number = getCallCount();
    advanceCallCount();

    email_request_callbacks[call_number] = callback;

    std::thread email_request_thread(post, call_number, "https://api.mod.works/oauth/emailrequest?shhh=secret", data, &onEmailRequested);
    email_request_thread.detach();

    writeLogLine("post detached", verbose);
  }

  void onEmailExchanged(int call_number, json response)
  {
    writeLogLine("onEmailExchanged call", verbose);
    access_token = response["access_token"];

    json token_json;
    token_json["access_token"] = response["access_token"];
    std::ofstream out(".modworks/token.json");
    out<<setw(4)<<token_json<<endl;
    out.close();

    int result_code = response["code"];
    email_exchange_callbacks[call_number]->callback(result_code);
    email_exchange_callbacks.erase(call_number);
    writeLogLine("onEmailExchanged finished", verbose);
  }

  void emailExchange(string security_code, function< void(int) > callback)
  {
    writeLogLine("emailExchange call", verbose);
    map<string, string> data;
    data["api_key"] = api_key;
    data["security_code"] = security_code;

    int call_number = getCallCount();
    advanceCallCount();

    email_exchange_callbacks[call_number] = new EmailExchangeParams;
    email_exchange_callbacks[call_number]->callback = callback;

    std::thread email_exchage_thread(post, call_number, "https://api.mod.works/oauth/emailexchange?shhh=secret",data, &onEmailExchanged);
    email_exchage_thread.detach();

    writeLogLine("post detached", verbose);
  }

  bool isLoggedIn()
  {
    return access_token!="";
  }

  void logout()
  {
    access_token = "";

    json empty_json;
    std::ofstream out(".modworks/token.json");
    out<<setw(4)<<empty_json<<endl;
    out.close();
  }
}
