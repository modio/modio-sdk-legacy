#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::getModTags(u32 mod_id, const std::function<void(const modio::Response &response, std::vector<modio::Tag> tags)> &callback)
{
  const struct GetModTagsCall *get_mod_tags_call = new GetModTagsCall{callback};
  get_mod_tags_calls[this->current_call_id] = (GetModTagsCall *)get_mod_tags_call;

  modioGetModTags((void *)new u32(this->current_call_id), mod_id, &onGetModTags);

  this->current_call_id++;
}

void Instance::addModTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response &response)> &callback)
{
  char **tags_array = new char *[tags.size()];
  for (int i = 0; i < (int)tags.size(); i++)
  {
    tags_array[i] = new char[tags[i].size() + 1];
    strcpy(tags_array[i], (char *)tags[i].c_str());
  }

  const struct AddModTagsCall *add_mod_tags_call = new AddModTagsCall{callback};
  add_mod_tags_calls[this->current_call_id] = (AddModTagsCall *)add_mod_tags_call;

  modioAddModTags((void *)new u32(this->current_call_id), mod_id, tags_array, (u32)tags.size(), &onAddModTags);

  this->current_call_id++;

  for (int i = 0; i < (int)tags.size(); i++)
    delete[] tags_array[i];
  delete[] tags_array;
}

void Instance::deleteModTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response &response)> &callback)
{
  char **tags_array = new char *[tags.size()];
  for (int i = 0; i < (int)tags.size(); i++)
  {
    tags_array[i] = new char[tags[i].size() + 1];
    strcpy(tags_array[i], (char *)tags[i].c_str());
  }

  const struct DeleteModTagsCall *delete_mod_tags_call = new DeleteModTagsCall{callback};
  delete_mod_tags_calls[this->current_call_id] = (DeleteModTagsCall *)delete_mod_tags_call;

  modioDeleteModTags((void *)new u32(this->current_call_id), mod_id, tags_array, (u32)tags.size(), &onDeleteModTags);

  this->current_call_id++;

  for (int i = 0; i < (int)tags.size(); i++)
    delete[] tags_array[i];
  delete[] tags_array;
}
} // namespace modio
