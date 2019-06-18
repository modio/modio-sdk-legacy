#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::getAllMetadataKVP(u32 mod_id, const std::function<void(const modio::Response& response, std::vector<modio::MetadataKVP> metadata_kvp)>& callback)
  {
    struct GetAllMetadataKVPCall* get_all_metadata_kvp_call = new GetAllMetadataKVPCall{callback};
    get_all_metadata_kvp_calls[current_call_id] = get_all_metadata_kvp_call;

    modioGetAllMetadataKVP((void*)((uintptr_t)current_call_id), mod_id, &onGetAllMetadataKVP);

    current_call_id++;
  }

  void Instance::addMetadataKVP(u32 mod_id, std::map<std::string, std::string> metadata_kvp, const std::function<void(const modio::Response& response)>& callback)
  {
    char** metadata_kvp_array = new char*[metadata_kvp.size()];
    u32 i = 0;
    for(const auto &current_metadata_kvp : metadata_kvp)
    {
      std::string metadata_kvp_parameterized = current_metadata_kvp.first + ":" + current_metadata_kvp.second;
      metadata_kvp_array[i] = new char[metadata_kvp_parameterized.size() + 1];
      strcpy(metadata_kvp_array[i], metadata_kvp_parameterized.c_str());
      i++;
    }

    struct GenericCall* add_metadata_kvp_call = new GenericCall{callback};
    add_metadata_kvp_calls[current_call_id] = add_metadata_kvp_call;

    modioAddMetadataKVP((void*)((uintptr_t)current_call_id), mod_id, metadata_kvp_array, (u32)metadata_kvp.size(), &onAddMetadataKVP);
    
    current_call_id++;

    for(i=0; i<metadata_kvp.size(); i++)
      delete[] metadata_kvp_array[i];
    delete[] metadata_kvp_array;
  }

  void Instance::deleteMetadataKVP(u32 mod_id, std::map< std::string, std::string > metadata_kvp, const std::function<void(const modio::Response& response)>& callback)
  {
    char** metadata_kvp_array = new char*[metadata_kvp.size()];
    u32 i = 0;
    for(const auto &current_metadata_kvp : metadata_kvp)
    {
      std::string metadata_kvp_parameterized = current_metadata_kvp.first + ":" + current_metadata_kvp.second;
      metadata_kvp_array[i] = new char[metadata_kvp_parameterized.size() + 1];
      strcpy(metadata_kvp_array[i], metadata_kvp_parameterized.c_str());
      i++;
    }

    struct GenericCall* delete_metadata_kvp_call = new GenericCall{callback};
    delete_metadata_kvp_calls[current_call_id] = delete_metadata_kvp_call;

    modioDeleteMetadataKVP((void*)((uintptr_t)current_call_id), mod_id, metadata_kvp_array, (u32)metadata_kvp.size(), &onDeleteMetadataKVP);

    current_call_id++;

    for(i=0; i<metadata_kvp.size(); i++)
      delete[] metadata_kvp_array[i];
    delete[] metadata_kvp_array;
  }
}
