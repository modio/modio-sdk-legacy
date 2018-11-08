#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, SubscribeToModCall *> subscribe_to_mod_calls;
std::map<u32, GenericCall *> unsubscribe_from_mod_calls;

void onSubscribeToMod(void *object, ModioResponse modio_response, ModioMod mod)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  modio::Mod modio_mod;

  if (modio_response.code == 201)
  {
    modio_mod.initialize(mod);
  }

  subscribe_to_mod_calls[call_id]->callback((const Response &)response, modio_mod);

  delete (u32 *)object;
  delete subscribe_to_mod_calls[call_id];
  subscribe_to_mod_calls.erase(call_id);
}

void onUnsubscribeFromMod(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  unsubscribe_from_mod_calls[call_id]->callback((const Response &)response);

  delete (u32 *)object;
  delete unsubscribe_from_mod_calls[call_id];
  unsubscribe_from_mod_calls.erase(call_id);
}

void clearSubscriptionRequestCalls()
{
  for (auto subscribe_to_mod_call : subscribe_to_mod_calls)
    delete subscribe_to_mod_call.second;
  subscribe_to_mod_calls.clear();

  for (auto unsubscribe_from_mod_call : unsubscribe_from_mod_calls)
    delete unsubscribe_from_mod_call.second;
  unsubscribe_from_mod_calls.clear();
}
} // namespace modio
