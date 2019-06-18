#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GenericCall *> add_mod_rating_calls;

void onAddModRating(void *object, ModioResponse modio_response)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;
  response.initialize(modio_response);

  add_mod_rating_calls[call_id]->callback(response);

  delete add_mod_rating_calls[call_id];
  add_mod_rating_calls.erase(call_id);
}

void clearRatingsRequestCalls()
{
  for (auto add_mod_rating_call : add_mod_rating_calls)
    delete add_mod_rating_call.second;
  add_mod_rating_calls.clear();
}
} // namespace modio
