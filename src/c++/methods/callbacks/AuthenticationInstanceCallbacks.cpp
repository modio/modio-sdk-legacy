#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GenericCall *> email_request_calls;
std::map<u32, GenericCall *> email_exchange_calls;

void onEmailRequest(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;

  response.initialize(modio_response);

  email_request_calls[call_id]->callback((const modio::Response &)response);

  delete (u32 *)object;
  delete email_request_calls[call_id];
  email_request_calls.erase(call_id);
}

void onEmailExchange(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  email_exchange_calls[call_id]->callback((const modio::Response &)response);

  delete (u32 *)object;
  delete email_exchange_calls[call_id];
  email_exchange_calls.erase(call_id);
}

void clearAuthenticationRequestCalls()
{
  for (auto email_request_call : email_request_calls)
    delete email_request_call.second;
  email_request_calls.clear();

  for (auto email_exchange_call : email_exchange_calls)
    delete email_exchange_call.second;
  email_exchange_calls.clear();
}
} // namespace modio
