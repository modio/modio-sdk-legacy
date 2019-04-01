#include "c/methods/callbacks/ModEventCallbacks.h"

std::map<u32, GetEventsParams *> get_events_callbacks;
std::map<u32, GetAllEventsParams *> get_all_events_callbacks;

void modioOnGetAllEvents(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioModEvent *events_array = NULL;
  u32 events_array_size = 0;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      events_array_size = (u32)response_json["data"].size();
      events_array = new ModioModEvent[events_array_size];

      for (u32 i = 0; i < events_array_size; i++)
        modioInitModEvent(&(events_array[i]), response_json["data"][i]);
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  get_all_events_callbacks[call_number]->callback(get_all_events_callbacks[call_number]->object, response, events_array, events_array_size);

  delete get_all_events_callbacks[call_number];
  get_all_events_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < events_array_size; i++)
    modioFreeModEvent(&(events_array[i]));
  if (events_array)
    delete[] events_array;
}

void modioOnGetEvents(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  ModioModEvent *events_array = NULL;
  u32 events_array_size = 0;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      events_array_size = (u32)response_json["data"].size();
      events_array = new ModioModEvent[events_array_size];

      for (u32 i = 0; i < events_array_size; i++)
        modioInitModEvent(&(events_array[i]), response_json["data"][i]);
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }
  get_events_callbacks[call_number]->callback(get_events_callbacks[call_number]->object, response, events_array, events_array_size);

  delete get_events_callbacks[call_number];
  get_events_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < events_array_size; i++)
    modioFreeModEvent(&(events_array[i]));
  if (events_array)
    delete[] events_array;
}

void clearModEventCallbackParams()
{
  for (auto get_events_callback : get_events_callbacks)
    delete get_events_callback.second;
  get_events_callbacks.clear();

  for (auto get_all_events_callback : get_all_events_callbacks)
    delete get_all_events_callback.second;
  get_all_events_callbacks.clear();
}