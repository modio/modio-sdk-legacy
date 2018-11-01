#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GetAllMetadataKVPCall *> get_all_metadata_kvp_calls;
std::map<u32, GenericCall *> add_metadata_kvp_calls;
std::map<u32, GenericCall *> delete_metadata_kvp_calls;

void onGetAllMetadataKVP(void *object, ModioResponse modio_response, ModioMetadataKVP *metadata_kvp_array, u32 metadata_kvp_array_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::MetadataKVP> metadata_kvp_vector;
  metadata_kvp_vector.resize(metadata_kvp_array_size);
  for (u32 i = 0; i < metadata_kvp_array_size; i++)
  {
    metadata_kvp_vector[i].initialize(metadata_kvp_array[i]);
  }
  get_all_metadata_kvp_calls[call_id]->callback((const Response &)response, metadata_kvp_vector);

  delete get_all_metadata_kvp_calls[call_id];
  delete (u32 *)object;
  get_all_metadata_kvp_calls.erase(call_id);
}

void onAddMetadataKVP(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  add_metadata_kvp_calls[call_id]->callback((const Response &)response);
  delete add_metadata_kvp_calls[call_id];
  delete (u32 *)object;
  add_metadata_kvp_calls.erase(call_id);
}

void onDeleteMetadataKVP(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  delete_metadata_kvp_calls[call_id]->callback((const Response &)response);
  delete delete_metadata_kvp_calls[call_id];
  delete (u32 *)object;
  delete_metadata_kvp_calls.erase(call_id);
}

void clearMetadataKVPRequestCalls()
{
  for (auto get_all_metadata_kvp_call : get_all_metadata_kvp_calls)
    delete get_all_metadata_kvp_call.second;
  get_all_metadata_kvp_calls.clear();

  for (auto add_metadata_kvp_call : add_metadata_kvp_calls)
    delete add_metadata_kvp_call.second;
  add_metadata_kvp_calls.clear();

  for (auto delete_metadata_kvp_call : delete_metadata_kvp_calls)
    delete delete_metadata_kvp_call.second;
  delete_metadata_kvp_calls.clear();
}
} // namespace modio
