#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GetModTagsCall *> get_mod_tags_calls;
std::map<u32, AddModTagsCall *> add_mod_tags_calls;
std::map<u32, DeleteModTagsCall *> delete_mod_tags_calls;

void onGetModTags(void *object, ModioResponse modio_response, ModioTag *tags_array, u32 tags_array_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Tag> tags_vector;
  tags_vector.resize(tags_array_size);
  for (u32 i = 0; i < tags_array_size; i++)
  {
    tags_vector[i].initialize(tags_array[i]);
  }
  get_mod_tags_calls[call_id]->callback((const Response &)response, tags_vector);

  delete get_mod_tags_calls[call_id];
  delete (u32 *)object;
  get_mod_tags_calls.erase(call_id);
}

void onAddModTags(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  add_mod_tags_calls[call_id]->callback((const Response &)response);
  delete add_mod_tags_calls[call_id];
  delete (u32 *)object;
  add_mod_tags_calls.erase(call_id);
}

void onDeleteModTags(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  delete_mod_tags_calls[call_id]->callback((const Response &)response);
  delete delete_mod_tags_calls[call_id];
  delete (u32 *)object;
  delete_mod_tags_calls.erase(call_id);
}

void clearTagsRequestCalls()
{
  for (auto get_mod_tags_call : get_mod_tags_calls)
    delete get_mod_tags_call.second;
  get_mod_tags_calls.clear();

  for (auto add_mod_tags_call : add_mod_tags_calls)
    delete add_mod_tags_call.second;
  add_mod_tags_calls.clear();

  for (auto delete_mod_tags_call : delete_mod_tags_calls)
    delete delete_mod_tags_call.second;
  delete_mod_tags_calls.clear();
}
} // namespace modio
