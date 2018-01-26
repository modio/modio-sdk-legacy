#include "c++/ModIOInstance.h"

namespace modio
{
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
}
