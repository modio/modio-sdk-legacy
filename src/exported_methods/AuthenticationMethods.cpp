#include "exported_methods/AuthenticationMethods.h"

typedef void (*ScriptFunction)(void);

map< int,void (*)(ModioResponse* response, char* message) > email_request_callbacks;
map< int,void (*)(ModioResponse* response) > email_exchange_callbacks;

void onEmailRequested(int call_number, ModioResponse* response, json response_json)
{
  string message_str = "";
  if(modio::hasKey(response_json,"message"))
    message_str = response_json["message"];
  char* message = new char[message_str.size() + 1];
  strcpy(message, message_str.c_str());
  email_request_callbacks[call_number](response, message);
  email_request_callbacks.erase(call_number);
}

void modioEmailRequest(char* email, void (*callback)(ModioResponse* response, char* message))
{
  map<string, string> data;
  data["api_key"] = modio::API_KEY;
  data["email"] = email;

  vector<string> headers;

  int call_number = modio::curlwrapper::getCallCount();
  modio::curlwrapper::advanceCallCount();

  email_request_callbacks[call_number] = callback;

  std::thread email_request_thread(modio::curlwrapper::post, call_number, modio::MODIO_URL + "oauth/emailrequest?shhh=secret", headers, data, &onEmailRequested);
  email_request_thread.detach();
}

void onEmailExchanged(int call_number, ModioResponse* response, json response_json)
{
  if(response->code == 200)
  {
    modio::ACCESS_TOKEN = response_json["access_token"];
    json token_json;
    token_json["access_token"] = response_json["access_token"];
    std::ofstream out(modio::getModIODirectory() + "token.json");
    out<<setw(4)<<token_json<<endl;
    out.close();
  }

  email_exchange_callbacks[call_number](response);
  email_exchange_callbacks.erase(call_number);
}

void modioEmailExchange(char* security_code, void (*callback)(ModioResponse* response))
{
  map<string, string> data;
  data["api_key"] = modio::API_KEY;
  data["security_code"] = security_code;

  vector<string> headers;

  int call_number = modio::curlwrapper::getCallCount();
  modio::curlwrapper::advanceCallCount();

  email_exchange_callbacks[call_number] = callback;

  std::thread email_exchage_thread(modio::curlwrapper::post, call_number, modio::MODIO_URL + "oauth/emailexchange?shhh=secret", headers, data, &onEmailExchanged);
  email_exchage_thread.detach();
}

bool modioIsLoggedIn()
{
  return modio::ACCESS_TOKEN!="";
}

void modioLogout()
{
  modio::ACCESS_TOKEN = "";

  json empty_json;
  std::ofstream out(modio::getModIODirectory() + "token.json");
  out<<setw(4)<<empty_json<<endl;
  out.close();
}
