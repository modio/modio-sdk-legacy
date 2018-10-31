#include "c/methods/callbacks/MetadataKVPCallbacks.h"

std::map< u32, GetAllMetadataKVPParams* > get_all_metadata_kvp_callbacks;
std::map< u32, GenericRequestParams* > add_metadata_kvp_callbacks;
std::map< u32, GenericRequestParams* > delete_metadata_kvp_callbacks;

void modioOnGetAllMetadataKVP(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  ModioMetadataKVP* metadata_kvp_array = NULL;
  u32 metadata_kvp_array_size = 0;

  if(response.code == 200)
  {
    if(modio::hasKey(response_json, "data"))
    {
      metadata_kvp_array_size = (u32)response_json["data"].size();
      metadata_kvp_array = new ModioMetadataKVP[metadata_kvp_array_size];
      for(u32 i=0; i<metadata_kvp_array_size; i++)
        modioInitMetadataKVP(&(metadata_kvp_array[i]), response_json["data"][i]);
    }else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  get_all_metadata_kvp_callbacks[call_number]->callback(get_all_metadata_kvp_callbacks[call_number]->object, response, metadata_kvp_array, metadata_kvp_array_size);
  
  delete get_all_metadata_kvp_callbacks[call_number];
  get_all_metadata_kvp_callbacks.erase(call_number);
  
  modioFreeResponse(&response);
  for(u32 i=0; i<metadata_kvp_array_size; i++)
    modioFreeMetadataKVP(&(metadata_kvp_array[i]));
  if(metadata_kvp_array)
    delete[] metadata_kvp_array;
}

void modioOnAddMetadataKVP(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  add_metadata_kvp_callbacks[call_number]->callback(add_metadata_kvp_callbacks[call_number]->object, response);
  
  delete add_metadata_kvp_callbacks[call_number];
  add_metadata_kvp_callbacks.erase(call_number);
  
  modioFreeResponse(&response);
}

void modioOnDeleteMetadataKVP(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  delete_metadata_kvp_callbacks[call_number]->callback(delete_metadata_kvp_callbacks[call_number]->object, response);
  
  delete delete_metadata_kvp_callbacks[call_number];
  delete_metadata_kvp_callbacks.erase(call_number);
  
  modioFreeResponse(&response);
}

void clearMetadataKVPCallbackParams()
{
  for (auto get_all_metadata_kvp_callback : get_all_metadata_kvp_callbacks)
    delete get_all_metadata_kvp_callback.second;
  get_all_metadata_kvp_callbacks.clear();

  for (auto add_metadata_kvp_callback : add_metadata_kvp_callbacks)
    delete add_metadata_kvp_callback.second;
  add_metadata_kvp_callbacks.clear();

  for (auto delete_metadata_kvp_callback : delete_metadata_kvp_callbacks)
    delete delete_metadata_kvp_callback.second;
  delete_metadata_kvp_callbacks.clear();
}