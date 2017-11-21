#include "ModIOInstance.h"

namespace modio
{
  int current_call_id = 0;

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
    const std::function<void(void* object, const ModioResponse&, const std::string&)>* callback;
  };

  map<int, EmailRequestCall*> email_request_calls;

  void onEmailRequest(void* object, ModioResponse response, char* message)
  {
    int call_id = *((int*)object);

    const std::function<void(void* object, const ModioResponse&, const std::string&)> callback = *(email_request_calls[call_id]->callback);
    callback(email_request_calls[call_id]->object, (const ModioResponse&)response, message);

    delete (int*)object;
    delete email_request_calls[call_id];
    email_request_calls.erase(call_id);
    delete[] message;
  }

  bool Instance::emailRequest(void* object, const std::string& email, const std::function<void(void* object, const ModioResponse&, const std::string&)>& callback)
  {
    email_request_calls[current_call_id] = new EmailRequestCall;
    email_request_calls[current_call_id]->object = object;
    email_request_calls[current_call_id]->callback = &callback;

    modioEmailRequest((void*)new int(current_call_id), (char*)email.c_str(), &onEmailRequest);

    current_call_id++;

    return true;
  }

  struct EmailExchangeCall
  {
    void* object;
    const std::function<void(void* object, const ModioResponse&)> callback;
  };

  map<int, EmailExchangeCall*> email_exchange_calls;

  void onEmailExchange(void* object, ModioResponse response)
  {
    int call_id = *((int*)object);

    const std::function<void(void* object, const ModioResponse&)> callback = email_exchange_calls[call_id]->callback;
    callback(email_exchange_calls[call_id]->object, (const ModioResponse&)response);
    delete (int*)object;
    delete email_request_calls[call_id];
    email_request_calls.erase(call_id);
  }

  bool Instance::emailExchange(void* object, const std::string& security_code, const std::function<void(void* object, const ModioResponse&)>& callback) const
  {
    const struct EmailExchangeCall* email_exchange_call = new EmailExchangeCall{object, callback};
    email_exchange_calls[current_call_id] = (EmailExchangeCall*)email_exchange_call;

    modioEmailExchange((void*)new int(current_call_id), (char*)security_code.c_str(), &onEmailExchange);

    current_call_id++;

    return true;
  }
}
