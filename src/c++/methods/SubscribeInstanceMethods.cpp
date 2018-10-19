#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::subscribeToMod(u32 mod_id, const std::function<void(const modio::Response &response, const modio::Mod &mod)> &callback)
{
  const struct SubscribeToModCall *subscribe_to_mod_call = new SubscribeToModCall{callback};
  subscribe_to_mod_calls[this->current_call_id] = (SubscribeToModCall *)subscribe_to_mod_call;

  modioSubscribeToMod((void *)new u32(this->current_call_id), mod_id, &onSubscribeToMod);

  this->current_call_id++;
}

void Instance::unsubscribeFromMod(u32 mod_id, const std::function<void(const modio::Response &response)> &callback)
{
  const struct UnsubscribeFromModCall *unsubscribe_from_mod_call = new UnsubscribeFromModCall{callback};
  unsubscribe_from_mod_calls[this->current_call_id] = (UnsubscribeFromModCall *)unsubscribe_from_mod_call;

  modioUnsubscribeFromMod((void *)new u32(this->current_call_id), mod_id, &onUnsubscribeFromMod);

  this->current_call_id++;
}
} // namespace modio
