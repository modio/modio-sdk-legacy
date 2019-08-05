#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::addModRating(u32 mod_id, bool vote_up, const std::function<void(const modio::Response &response)> &callback)
{
  struct GenericCall *add_mod_rating_call = new GenericCall{callback};
  add_mod_rating_calls[current_call_id] = add_mod_rating_call;

  modioAddModRating((void*)((uintptr_t)current_call_id), mod_id, vote_up, &onAddModRating);

  current_call_id++;
}

u32 Instance::getUserModRating(u32 mod_id)
{
  return modioGetUserModRating(mod_id);
}
} // namespace modio
