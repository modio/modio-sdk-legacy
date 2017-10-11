#include "AuthenticationMethods.h"

namespace modio
{
  map< int,function<void(int, string)> > email_request_callbacks;
  map< int,function<void(int, string)> > email_exchange_callbacks;

  void onEmailRequested(int call_number, int response_code, string message, json response)
  {
    email_request_callbacks[call_number](response_code, message);
    email_request_callbacks.erase(call_number);
  }

  void emailRequest(string email, function< void(int response_code, string message) > callback)
  {
    map<string, string> data;
    data["api_key"] = api_key;
    data["email"] = email;

    vector<string> headers;

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    email_request_callbacks[call_number] = callback;

    std::thread email_request_thread(curlwrapper::post, call_number, MODIO_URL + "oauth/emailrequest?shhh=secret", headers, data, &onEmailRequested);
    email_request_thread.detach();
  }

  void onEmailExchanged(int call_number, int response_code, string message, json response)
  {
    if(response_code == 200)
    {
      access_token = response["access_token"];
      json token_json;
      token_json["access_token"] = response["access_token"];
      std::ofstream out(getModIODirectory() + "token.json");
      out<<setw(4)<<token_json<<endl;
      out.close();
    }

    email_exchange_callbacks[call_number](response_code, message);
    email_exchange_callbacks.erase(call_number);
  }

  void emailExchange(string security_code, function< void(int response_code, string message) > callback)
  {
    map<string, string> data;
    data["api_key"] = api_key;
    data["security_code"] = security_code;

    vector<string> headers;

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    email_exchange_callbacks[call_number] = callback;

    std::thread email_exchage_thread(curlwrapper::post, call_number, MODIO_URL + "oauth/emailexchange?shhh=secret", headers, data, &onEmailExchanged);
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
    std::ofstream out(getModIODirectory() + "token.json");
    out<<setw(4)<<empty_json<<endl;
    out.close();
  }
}
