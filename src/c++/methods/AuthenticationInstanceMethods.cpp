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

void Instance::emailRequest(const std::string &email, const std::function<void(const modio::Response &)> &callback)
{
  const struct EmailRequestCall *email_request_call = new EmailRequestCall{callback};
  email_request_calls[this->current_call_id] = (EmailRequestCall *)email_request_call;

  modioEmailRequest((void *)new u32(this->current_call_id), (char *)email.c_str(), &onEmailRequest);

  this->current_call_id++;
}

void Instance::emailExchange(const std::string &security_code, const std::function<void(const modio::Response &)> &callback)
{
  const struct EmailExchangeCall *email_exchange_call = new EmailExchangeCall{callback};
  email_exchange_calls[this->current_call_id] = (EmailExchangeCall *)email_exchange_call;

  modioEmailExchange((void *)new u32(this->current_call_id), (char *)security_code.c_str(), &onEmailExchange);

  this->current_call_id++;
}
} // namespace modio
