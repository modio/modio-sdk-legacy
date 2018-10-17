#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::getEvents(u32 mod_id, modio::FilterCreator &filter, const std::function<void(const modio::Response &, const std::vector<modio::Event> &events)> &callback)
{
  const struct GetEventsCall *get_events_call = new GetEventsCall{callback};
  get_events_calls[this->current_call_id] = (GetEventsCall *)get_events_call;

  modioGetEvents((void *)new u32(this->current_call_id), mod_id, *filter.getFilter(), &onGetEvents);

  this->current_call_id++;
}

void Instance::getAllEvents(modio::FilterCreator &filter, const std::function<void(const modio::Response &, const std::vector<modio::Event> &events)> &callback)
{
  const struct GetAllEventsCall *get_all_events_call = new GetAllEventsCall{callback};
  get_all_events_calls[this->current_call_id] = (GetAllEventsCall *)get_all_events_call;

  modioGetAllEvents((void *)new u32(this->current_call_id), *filter.getFilter(), &onGetAllEvents);

  this->current_call_id++;
}

void Instance::setEventListener(const std::function<void(const modio::Response &, const std::vector<modio::Event> &events)> &callback)
{
  set_event_listener_call = new SetEventListenerCall{callback};
  modioSetEventListener(&onSetEventListener);
}
} // namespace modio
