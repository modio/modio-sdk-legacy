#include "c++/ModIOInstance.h"

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
    const std::function<void(const modio::Response&)> callback;
  };

  struct EmailExchangeCall
  {
    const std::function<void(const modio::Response&)> callback;
  };

  std::map<u32, EmailRequestCall*> email_request_calls;
  std::map<u32, EmailExchangeCall*> email_exchange_calls;

  void onEmailRequest(void* object, ModioResponse modio_response)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;

    response.initialize(modio_response);

    email_request_calls[call_id]->callback((const modio::Response&)response);

    delete (u32*)object;
    delete email_request_calls[call_id];
    email_request_calls.erase(call_id);
  }

  void onEmailExchange(void* object, ModioResponse modio_response)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    email_exchange_calls[call_id]->callback((const modio::Response&)response);

    delete (u32*)object;
    delete email_request_calls[call_id];
    email_request_calls.erase(call_id);
  }

  void Instance::emailRequest(const std::string& email, const std::function<void(const modio::Response&)>& callback)
  {
    const struct EmailRequestCall* email_request_call = new EmailRequestCall{callback};
    email_request_calls[this->current_call_id] = (EmailRequestCall*)email_request_call;

    modioEmailRequest((void*)new u32(this->current_call_id), (char*)email.c_str(), &onEmailRequest);

    this->current_call_id++;
  }

  void Instance::emailExchange(const std::string& security_code, const std::function<void(const modio::Response&)>& callback)
  {
    const struct EmailExchangeCall* email_exchange_call = new EmailExchangeCall{callback};
    email_exchange_calls[this->current_call_id] = (EmailExchangeCall*)email_exchange_call;

    modioEmailExchange((void*)new u32(this->current_call_id), (char*)security_code.c_str(), &onEmailExchange);

    this->current_call_id++;
  }
}
