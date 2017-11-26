#include "ModIOInstance.h"

namespace modio
{
  bool Instance::isLoggedIn() const
  {
    return modioIsLoggedIn();
  }

  void Instance::logout() const
  {
    modioLogout();
  }

  struct EmailRequestCall
  {
    void* object;
    const std::function<void(void* object, const modio::Response&, const std::string&)> callback;
  };

  struct EmailExchangeCall
  {
    void* object;
    const std::function<void(void* object, const modio::Response&)> callback;
  };

  std::map<int, EmailRequestCall*> email_request_calls;
  std::map<int, EmailExchangeCall*> email_exchange_calls;

  void onEmailRequest(void* object, ModioResponse modio_response, char* message)
  {
    int call_id = *((int*)object);

    modio::Response response;

    response.initialize(modio_response);

    email_request_calls[call_id]->callback(email_request_calls[call_id]->object, (const modio::Response&)response, message);

    delete (int*)object;
    delete email_request_calls[call_id];
    email_request_calls.erase(call_id);
    delete[] message;
  }

  void onEmailExchange(void* object, ModioResponse modio_response)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);

    email_exchange_calls[call_id]->callback(email_exchange_calls[call_id]->object, (const modio::Response&)response);

    delete (int*)object;
    delete email_request_calls[call_id];
    email_request_calls.erase(call_id);
  }

  bool Instance::emailRequest(void* object, const std::string& email, const std::function<void(void* object, const modio::Response&, const std::string&)>& callback)
  {
    const struct EmailRequestCall* email_request_call = new EmailRequestCall{object, callback};
    email_request_calls[this->current_call_id] = (EmailRequestCall*)email_request_call;

    modioEmailRequest((void*)new int(this->current_call_id), (char*)email.c_str(), &onEmailRequest);

    this->current_call_id++;

    return true;
  }

  bool Instance::emailExchange(void* object, const std::string& security_code, const std::function<void(void* object, const modio::Response&)>& callback)
  {
    const struct EmailExchangeCall* email_exchange_call = new EmailExchangeCall{object, callback};
    email_exchange_calls[this->current_call_id] = (EmailExchangeCall*)email_exchange_call;

    modioEmailExchange((void*)new int(this->current_call_id), (char*)security_code.c_str(), &onEmailExchange);

    this->current_call_id++;

    return true;
  }
}
