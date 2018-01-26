#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::getTags(u32 mod_id, const std::function<void(const modio::Response& response, std::vector<modio::Tag> tags)>& callback)
  {
    const struct GetTagsCall* get_tags_call = new GetTagsCall{callback};
    get_tags_calls[this->current_call_id] = (GetTagsCall*)get_tags_call;

    modioGetTags((void*)new u32(this->current_call_id), mod_id, &onGetTags);

    this->current_call_id++;
  }

  void Instance::addTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response& response, u32 mod_id)>& callback)
  {
    char** tags_array = new char*[tags.size()];
    for(int i=0; i<tags.size(); i++)
    {
      tags_array[i] = new char[tags[i].size() + 1];
      strcpy(tags_array[i], (char*)tags[i].c_str());
    }

    const struct AddTagsCall* add_tags_call = new AddTagsCall{tags_array, (u32)tags.size(), callback};
    add_tags_calls[this->current_call_id] = (AddTagsCall*)add_tags_call;

    modioAddTags((void*)new u32(this->current_call_id), mod_id, tags_array, tags.size(), &onAddTags);
    this->current_call_id++;
  }

  void Instance::deleteTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response& response, u32 mod_id)>& callback)
  {
    char** tags_array = new char*[tags.size()];
    for(int i=0; i<tags.size(); i++)
    {
      tags_array[i] = new char[tags[i].size() + 1];
      strcpy(tags_array[i], (char*)tags[i].c_str());
    }

    const struct DeleteTagsCall* delete_tags_call = new DeleteTagsCall{tags_array, (u32)tags.size(), callback};
    delete_tags_calls[this->current_call_id] = (DeleteTagsCall*)delete_tags_call;

    modioDeleteTags((void*)new u32(this->current_call_id), mod_id, tags_array, tags.size(), &onDeleteTags);

    this->current_call_id++;
  }
}
