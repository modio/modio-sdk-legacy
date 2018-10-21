#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GetEventsCall *> get_events_calls;
std::map<u32, GetAllEventsCall *> get_all_events_calls;
SetEventListenerCall *set_event_listener_call;

void onGetEvents(void *object, ModioResponse modio_response, ModioEvent *events_array, u32 events_array_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Event> event_vector;
  event_vector.resize(events_array_size);
  for (u32 i = 0; i < events_array_size; i++)
  {
    event_vector[i].initialize(events_array[i]);
  }
  get_events_calls[call_id]->callback((const Response &)response, event_vector);

  delete get_events_calls[call_id];
  delete (u32 *)object;
  get_events_calls.erase(call_id);
}

void onGetAllEvents(void *object, ModioResponse modio_response, ModioEvent *events_array, u32 events_array_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Event> event_vector;
  event_vector.resize(events_array_size);
  for (u32 i = 0; i < events_array_size; i++)
  {
    event_vector[i].initialize(events_array[i]);
  }
  get_all_events_calls[call_id]->callback((const Response &)response, event_vector);

  delete get_all_events_calls[call_id];
  delete (u32 *)object;
  get_all_events_calls.erase(call_id);
}

void onSetEventListener(ModioResponse modio_response, ModioEvent *events_array, u32 events_array_size)
{
  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Event> events_vector;
  events_vector.resize(events_array_size);
  for (u32 i = 0; i < events_array_size; i++)
  {
    events_vector[i].initialize(events_array[i]);
  }
  set_event_listener_call->callback((const Response &)response, events_vector);
}

void clearModEventsRequestCalls()
{
  for (auto get_events_call : get_events_calls)
    delete get_events_call.second;
  get_events_calls.clear();

  for (auto get_all_events_call : get_all_events_calls)
    delete get_all_events_call.second;
  get_all_events_calls.clear();
}
} // namespace modio
