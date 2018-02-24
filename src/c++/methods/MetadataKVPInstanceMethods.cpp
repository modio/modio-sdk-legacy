#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::getMetadataKVP(u32 mod_id, const std::function<void(const modio::Response& response, std::vector<modio::MetadataKVP> metadata_kvp)>& callback)
  {
    const struct GetMetadataKVPCall* get_metadata_kvp_call = new GetMetadataKVPCall{callback};
    get_metadata_kvp_calls[this->current_call_id] = (GetMetadataKVPCall*)get_metadata_kvp_call;

    modioGetMetadataKVP((void*)new u32(this->current_call_id), mod_id, &onGetMetadataKVP);

    this->current_call_id++;
  }

  void Instance::addMetadataKVP(u32 mod_id, std::vector< std::pair< std::string, std::string > > metadata_kvp, const std::function<void(const modio::Response& response)>& callback)
  {
    char** metadata_kvp_array = new char*[metadata_kvp.size()];
    for(int i=0; i<(int)metadata_kvp.size(); i++)
    {
      std::string metadata_kvp_parameterized = metadata_kvp[i].first + ":" + metadata_kvp[i].first;
      metadata_kvp_array[i] = new char[metadata_kvp_parameterized.size() + 1];
      strcpy(metadata_kvp_array[i], (char*)metadata_kvp_parameterized.c_str());
    }

    const struct AddMetadataKVPCall* add_metadata_kvp_call = new AddMetadataKVPCall{metadata_kvp_array, (u32)metadata_kvp.size(), callback};
    add_metadata_kvp_calls[this->current_call_id] = (AddMetadataKVPCall*)add_metadata_kvp_call;

    modioAddMetadataKVP((void*)new u32(this->current_call_id), mod_id, metadata_kvp_array, (u32)metadata_kvp.size(), &onAddMetadataKVP);
    this->current_call_id++;
  }

  void Instance::deleteMetadataKVP(u32 mod_id, std::vector< std::pair< std::string, std::string > > metadata_kvp, const std::function<void(const modio::Response& response)>& callback)
  {
    char** metadata_kvp_array = new char*[metadata_kvp.size()];
    for(int i=0; i<(int)metadata_kvp.size(); i++)
    {
      std::string metadata_kvp_parameterized = metadata_kvp[i].first + ":" + metadata_kvp[i].first;
      metadata_kvp_array[i] = new char[metadata_kvp_parameterized.size() + 1];
      strcpy(metadata_kvp_array[i], (char*)metadata_kvp_parameterized.c_str());
    }

    const struct DeleteMetadataKVPCall* delete_metadata_kvp_call = new DeleteMetadataKVPCall{metadata_kvp_array, (u32)metadata_kvp.size(), callback};
    delete_metadata_kvp_calls[this->current_call_id] = (DeleteMetadataKVPCall*)delete_metadata_kvp_call;

    modioDeleteMetadataKVP((void*)new u32(this->current_call_id), mod_id, metadata_kvp_array, (u32)metadata_kvp.size(), &onDeleteMetadataKVP);

    this->current_call_id++;
  }
}
