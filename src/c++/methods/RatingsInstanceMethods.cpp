#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::addModRating(u32 mod_id, bool vote_up, const std::function<void(const modio::Response &response)> &callback)
{
  const struct AddModRatingCall *add_mod_rating_call = new AddModRatingCall{callback};
  add_mod_rating_calls[this->current_call_id] = (AddModRatingCall *)add_mod_rating_call;

  modioAddModRating((void *)new u32(this->current_call_id), mod_id, vote_up, &onAddModRating);

  this->current_call_id++;
}
} // namespace modio
