#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::subscribeToMod(u32 mod_id, const std::function<void(const modio::Response &response, const modio::Mod &mod)> &callback)
{
  struct SubscribeToModCall *subscribe_to_mod_call = new SubscribeToModCall{callback};
  subscribe_to_mod_calls[current_call_id] = subscribe_to_mod_call;

  modioSubscribeToMod((void*)((uintptr_t)current_call_id), mod_id, &onSubscribeToMod);

  current_call_id++;
}

void Instance::unsubscribeFromMod(u32 mod_id, const std::function<void(const modio::Response &response)> &callback)
{
  struct GenericCall *unsubscribe_from_mod_call = new GenericCall{callback};
  unsubscribe_from_mod_calls[current_call_id] = unsubscribe_from_mod_call;

  modioUnsubscribeFromMod((void*)((uintptr_t)current_call_id), mod_id, &onUnsubscribeFromMod);

  current_call_id++;
}

bool Instance::isCurrentUserSubscribed(u32 mod_id)
{
  return modioIsCurrentUserSubscribed(mod_id);
}

const std::vector<u32> Instance::getCurrentUserSubscriptions()
{
  std::vector<u32> return_value(modio::current_user_subscriptions.begin(), modio::current_user_subscriptions.end());
  return return_value;
}

} // namespace modio
