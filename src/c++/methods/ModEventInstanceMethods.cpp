#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::getModEvents(u32 mod_id, modio::FilterCreator& filter, const std::function<void(const modio::Response&, const std::vector<modio::ModEvent> & mod_events)>& callback)
  {
    const struct GetModEventsCall* get_mod_events_call = new GetModEventsCall{callback};
    get_mod_events_calls[this->current_call_id] = (GetModEventsCall*)get_mod_events_call;

    modioGetModEvents((void*)new u32(this->current_call_id), mod_id, *filter.getFilter(), &onGetModEvents);

    this->current_call_id++;
  }

  void Instance::getAllModEvents(modio::FilterCreator& filter, const std::function<void(const modio::Response&, const std::vector<modio::ModEvent> & mod_events)>& callback)
  {
    const struct GetAllModEventsCall* get_all_mod_events_call = new GetAllModEventsCall{callback};
    get_all_mod_events_calls[this->current_call_id] = (GetAllModEventsCall*)get_all_mod_events_call;

    modioGetAllModEvents((void*)new u32(this->current_call_id), *filter.getFilter(), &onGetAllModEvents);

    this->current_call_id++;
  }

  void Instance::setModEventListener(const std::function<void(const modio::Response&, const std::vector<modio::ModEvent> & mod_events)>& callback)
  {
    set_mod_event_listener_call = new SetModEventListenerCall{callback};
    modioSetModEventListener(&onSetModEventListener);
  }
}
