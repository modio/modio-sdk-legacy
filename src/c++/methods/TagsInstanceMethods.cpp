#include "c++/ModIOInstance.h"
#include "ModioUtility.h"
#include "c++/methods/callbacks/TagsInstanceCallbacks.h"

namespace modio
{
void Instance::getModTags(u32 mod_id, const std::function<void(const modio::Response &response, std::vector<modio::Tag> tags)> &callback)
{
  struct GetModTagsCall *get_mod_tags_call = new GetModTagsCall{callback};
  get_mod_tags_calls[current_call_id] = get_mod_tags_call;

  modioGetModTags((void*)((uintptr_t)current_call_id), mod_id, &onGetModTags);

  current_call_id++;
}

void Instance::addModTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response &response)> &callback)
{
  char **tags_array = new char *[tags.size()];
  for (size_t i = 0; i < tags.size(); i++)
  {
    tags_array[i] = new char[tags[i].size() + 1];
    strcpy(tags_array[i], tags[i].c_str());
  }

  struct GenericCall *add_mod_tags_call = new GenericCall{callback};
  add_mod_tags_calls[current_call_id] = add_mod_tags_call;

  modioAddModTags((void*)((uintptr_t)current_call_id), mod_id, tags_array, (u32)tags.size(), &onAddModTags);

  current_call_id++;

  for (size_t i = 0; i < tags.size(); i++)
    delete[] tags_array[i];
  delete[] tags_array;
}

void Instance::deleteModTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response &response)> &callback)
{
  char **tags_array = new char *[tags.size()];
  for (size_t i = 0; i < tags.size(); i++)
  {
    tags_array[i] = new char[tags[i].size() + 1];
    strcpy(tags_array[i], tags[i].c_str());
  }

  struct GenericCall *delete_mod_tags_call = new GenericCall{callback};
  delete_mod_tags_calls[current_call_id] = delete_mod_tags_call;

  modioDeleteModTags((void*)((uintptr_t)current_call_id), mod_id, tags_array, (u32)tags.size(), &onDeleteModTags);

  current_call_id++;

  for (size_t i = 0; i < tags.size(); i++)
    delete[] tags_array[i];
  delete[] tags_array;
}
} // namespace modio
