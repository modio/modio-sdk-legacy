#include "c/methods/callbacks/ModEventCallbacks.h"

std::map< u32, GetEventsParams* > get_events_callbacks;
std::map< u32, GetAllEventsParams* > get_all_events_callbacks;

void modioOnGetAllEvents(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioEvent* events_array = NULL;
  u32 events_array_size = 0;
  if(response.code == 200)
  {
    try
    {
      if(modio::hasKey(response_json, "data"))
      {
        events_array_size = (u32)response_json["data"].size();
        events_array = new ModioEvent[events_array_size];

        for(u32 i=0; i<events_array_size; i++)
        {
          modioInitEvent(&(events_array[i]), response_json["data"][i]);
        }
      }
    }catch(nlohmann::json::parse_error &e)
    {
      modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
    }
  }
  get_all_events_callbacks[call_number]->callback(get_all_events_callbacks[call_number]->object, response, events_array, events_array_size);

  for(u32 i=0; i<events_array_size; i++)
  {
    modioFreeEvent(&(events_array[i]));
  }

  if(events_array)
    delete[] events_array;
  delete get_all_events_callbacks[call_number];
  get_all_events_callbacks.erase(call_number);
}

void modioOnGetEvents(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioEvent* events_array = NULL;
  u32 events_array_size = 0;
  if(response.code == 200)
  {
    try
    {
      if(modio::hasKey(response_json, "data"))
      {
        events_array_size = (u32)response_json["data"].size();
        events_array = new ModioEvent[events_array_size];

        for(u32 i=0; i<events_array_size; i++)
        {
          modioInitEvent(&(events_array[i]), response_json["data"][i]);
        }
      }
    }catch(nlohmann::json::parse_error &e)
    {
      modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
    }
  }
  get_events_callbacks[call_number]->callback(get_events_callbacks[call_number]->object, response, events_array, events_array_size);

  for(u32 i=0; i<events_array_size; i++)
  {
    modioFreeEvent(&(events_array[i]));
  }

  if(events_array)
    delete[] events_array;
  delete get_events_callbacks[call_number];
  get_events_callbacks.erase(call_number);
}
