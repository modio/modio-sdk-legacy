#include "c/methods/AuthenticationMethods.h"

extern "C"
{
  struct EmailRequestParams
  {
    void* object;
    void (*callback)(void* object, ModioResponse response);
  };

  struct EmailExchangeParams
  {
    void* object;
    void (*callback)(void* object, ModioResponse response);
  };

  std::map< u32,EmailRequestParams* > email_request_params;
  std::map< u32,EmailExchangeParams* > email_exchange_params;

  void modioOnEmailRequested(u32 call_number, u32 response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    email_request_params[call_number]->callback(email_request_params[call_number]->object, response);
    delete email_request_params[call_number];
    email_request_params.erase(call_number);
    modioFreeResponse(&response);
  }

  void modioOnEmailExchanged(u32 call_number, u32 response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;
    if(response.code == 200)
    {
      modio::ACCESS_TOKEN = response_json["access_token"];
      json token_json;
      token_json["access_token"] = response_json["access_token"];
      std::ofstream out(modio::getModIODirectory() + "token.json");
      out<<std::setw(4)<<token_json<<std::endl;
      out.close();
    }
    email_exchange_params[call_number]->callback(email_exchange_params[call_number]->object, response);
    delete email_exchange_params[call_number];
    email_exchange_params.erase(call_number);
    modioFreeResponse(&response);
  }

  void modioEmailRequest(void* object, char* email, void (*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;
    data["api_key"] = modio::API_KEY;
    data["email"] = email;

    std::vector<std::string> headers;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    email_request_params[call_number] = new EmailRequestParams;
    email_request_params[call_number]->callback = callback;
    email_request_params[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "oauth/emailrequest";
    url += "?api_key=" + modio::API_KEY;
    url += "&email=" + std::string(email);

    modio::curlwrapper::post(call_number, url, headers, data, &modioOnEmailRequested);
  }

  void modioEmailExchange(void* object, char* security_code, void (*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;
    std::vector<std::string> headers;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();
    email_exchange_params[call_number] = new EmailExchangeParams;
    email_exchange_params[call_number]->callback = callback;
    email_exchange_params[call_number]->object = object;
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "oauth/emailexchange";
    url += "?api_key=" + modio::API_KEY;
    url += "&security_code=" + std::string(security_code);
    modio::curlwrapper::post(call_number, url, headers, data, &modioOnEmailExchanged);
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
    out<<std::setw(4)<<empty_json<<std::endl;
    out.close();
  }
}
