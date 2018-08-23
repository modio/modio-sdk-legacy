#include "c/methods/callbacks/TagCallbacks.h"

std::map< u32, GetModTagsParams* > get_mod_tags_callbacks;
std::map< u32, EditTagsParams* > add_mod_tags_callbacks;
std::map< u32, DeleteModTagsParams* > delete_mod_tags_callbacks;

void modioOnGetModTags(u32 call_number, u32 response_code, nlohmann::json  response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioTag* tags_array = NULL;
  u32 tags_array_size = 0;
  if(response.code == 200)
  {
    try
    {
      if(modio::hasKey(response_json, "data"))
      {
        tags_array_size = (u32)response_json["data"].size();
        tags_array = new ModioTag[tags_array_size];
        for(u32 i=0; i<tags_array_size; i++)
        {
          modioInitTag(&(tags_array[i]), response_json["data"][i]);
        }
      }
    }catch(nlohmann::json::parse_error &e)
    {
      modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
    }
  }
  get_mod_tags_callbacks[call_number]->callback(get_mod_tags_callbacks[call_number]->object, response, tags_array, tags_array_size);
  for(u32 i=0; i<tags_array_size; i++)
  {
    modioFreeTag(&(tags_array[i]));
  }
  if(tags_array)
    delete[] tags_array;
  delete get_mod_tags_callbacks[call_number];
  get_mod_tags_callbacks.erase(call_number);
}

void modioOnTagsAdded(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  add_mod_tags_callbacks[call_number]->callback(add_mod_tags_callbacks[call_number]->object, response);
  delete add_mod_tags_callbacks[call_number];
  add_mod_tags_callbacks.erase(call_number);
}

void modioOnTagsDeleted(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  delete_mod_tags_callbacks[call_number]->callback(delete_mod_tags_callbacks[call_number]->object, response);
  delete delete_mod_tags_callbacks[call_number];
  delete_mod_tags_callbacks.erase(call_number);
}
