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
  struct GenericCall *email_request_call = new GenericCall{callback};
  email_request_calls[current_call_id] = email_request_call;

  modioEmailRequest(new u32(current_call_id), email.c_str(), &onEmailRequest);

  current_call_id++;
}

void Instance::emailExchange(const std::string &security_code, const std::function<void(const modio::Response &)> &callback)
{
  struct GenericCall *email_exchange_call = new GenericCall{callback};
  email_exchange_calls[current_call_id] = email_exchange_call;

  modioEmailExchange(new u32(current_call_id), security_code.c_str(), &onEmailExchange);

  current_call_id++;
}

modio::User Instance::getCurrentUser()
{
  modio::User user;
  user.initialize(modioGetCurrentUser());
  return user;
}

} // namespace modio
