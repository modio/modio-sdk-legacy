#include "c++/ModIOInstance.h"

namespace modio
{
  struct GetTagsCall
  {
    const std::function<void(const modio::Response& response, std::vector<modio::Tag> tags)> callback;
  };

  struct AddTagsCall
  {
    char** tags_array;
    u32 tags_array_size;
    const std::function<void(const modio::Response& response, u32 mod_id)> callback;
  };

  struct DeleteTagsCall
  {
    char** tags_array;
    u32 tags_array_size;
    const std::function<void(const modio::Response& response, u32 mod_id)> callback;
  };

  std::map<u32, GetTagsCall*> get_tags_calls;
  std::map<u32, AddTagsCall*> add_tags_calls;
  std::map<u32, DeleteTagsCall*> delete_tags_calls;

  void onGetTags(void* object, ModioResponse modio_response, u32 mod_id, ModioTag* tags_array, u32 tags_array_size)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::Tag> tags_vector;
    tags_vector.resize(tags_array_size);
    for(u32 i=0; i < tags_array_size; i++)
    {
      tags_vector[i].initialize(tags_array[i]);
    }
    get_tags_calls[call_id]->callback((const Response&)response, tags_vector);

    delete get_tags_calls[call_id];
    delete (u32*)object;
    get_tags_calls.erase(call_id);
  }

  void onAddTags(void* object, ModioResponse modio_response, u32 mod_id)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    add_tags_calls[call_id]->callback((const Response&)response, mod_id);
    for(u32 i=0; i<add_tags_calls[call_id]->tags_array_size; i++)
      delete[] add_tags_calls[call_id]->tags_array[i];
    delete[] add_tags_calls[call_id]->tags_array;
    delete add_tags_calls[call_id];
    delete (u32*)object;
    add_tags_calls.erase(call_id);
  }

  void onDeleteTags(void* object, ModioResponse modio_response, u32 mod_id)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    delete_tags_calls[call_id]->callback((const Response&)response, mod_id);
    for(u32 i=0; i<delete_tags_calls[call_id]->tags_array_size; i++)
      delete[] delete_tags_calls[call_id]->tags_array[i];
    delete[] delete_tags_calls[call_id]->tags_array;
    delete delete_tags_calls[call_id];
    delete (u32*)object;
    delete_tags_calls.erase(call_id);
  }

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
