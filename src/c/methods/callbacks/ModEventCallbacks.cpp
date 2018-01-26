#include "c/methods/callbacks/ModEventCallbacks.h"

std::map< u32, GetAllModEventsParams* > get_all_mod_events_callbacks;

void modioOnGetAllModEvents(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioModEvent* mod_events_array = NULL;
  u32 mod_events_array_size = 0;
  if(response.code == 200)
  {
    try
    {
      if(modio::hasKey(response_json, "data"))
      {
        mod_events_array_size = response_json["data"].size();
        mod_events_array = new ModioModEvent[mod_events_array_size];

        for(u32 i=0; i<mod_events_array_size; i++)
        {
          modioInitModEvent(&(mod_events_array[i]), response_json["data"][i]);
        }
      }
    }catch(json::parse_error &e)
    {
      modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
    }
  }
  get_all_mod_events_callbacks[call_number]->callback(get_all_mod_events_callbacks[call_number]->object, response, mod_events_array, mod_events_array_size);

  for(u32 i=0; i<mod_events_array_size; i++)
  {
    modioFreeModEvent(&(mod_events_array[i]));
  }

  if(mod_events_array)
    delete[] mod_events_array;
  delete get_all_mod_events_callbacks[call_number];
  get_all_mod_events_callbacks.erase(call_number);
}
