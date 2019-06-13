#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::subscribeToMod(u32 mod_id, const std::function<void(const modio::Response &response, const modio::Mod &mod)> &callback)
{
  struct SubscribeToModCall *subscribe_to_mod_call = new SubscribeToModCall{callback};
  subscribe_to_mod_calls[current_call_id] = subscribe_to_mod_call;

  modioSubscribeToMod(new u32(current_call_id), mod_id, &onSubscribeToMod);

  current_call_id++;
}

void Instance::unsubscribeFromMod(u32 mod_id, const std::function<void(const modio::Response &response)> &callback)
{
  struct GenericCall *unsubscribe_from_mod_call = new GenericCall{callback};
  unsubscribe_from_mod_calls[current_call_id] = unsubscribe_from_mod_call;

  modioUnsubscribeFromMod(new u32(current_call_id), mod_id, &onUnsubscribeFromMod);

  current_call_id++;
}
} // namespace modio
