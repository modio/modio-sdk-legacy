#include "ModIOInstance.h"

namespace modio
{
  struct GetTagsCall
  {
    void* object;
    const std::function<void(void* object, const modio::Response& response, std::vector<modio::Tag> tags)> callback;
  };

  struct AddTagsCall
  {
    void* object;
    const std::function<void(void* object, const modio::Response& response, u32 mod_id, std::vector<modio::Tag> tags)> callback;
  };

  struct DeleteTagsCall
  {
    void* object;
    const std::function<void(void* object, const modio::Response& response, u32 mod_id, std::vector<modio::Tag> tags)> callback;
  };

  std::map<int, GetTagsCall*> get_tags_calls;
  std::map<int, AddTagsCall*> add_tags_calls;
  std::map<int, DeleteTagsCall*> delete_tags_calls;

  void onGetTags(void* object, ModioResponse modio_response, int mod_id, ModioTag* tags_array, int tags_array_size)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::Tag> tags_vector;
    tags_vector.resize(tags_array_size);
    for(int i=0; i < tags_array_size; i++)
    {
      tags_vector[i].initialize(tags_array[i]);
    }
    get_tags_calls[call_id]->callback(get_tags_calls[call_id]->object, (const Response&)response, tags_vector);

    delete (int*)object;
    delete[] tags_array;
    delete get_tags_calls[call_id];
    get_tags_calls.erase(call_id);
  }

  void onAddTags(void* object, ModioResponse modio_response, int mod_id, ModioTag* tags_array, int tags_array_size)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::Tag> tags_vector;
    tags_vector.resize(tags_array_size);
    for(int i=0; i < tags_array_size; i++)
    {
      tags_vector[i].initialize(tags_array[i]);
    }

    add_tags_calls[call_id]->callback(add_tags_calls[call_id]->object, (const Response&)response, mod_id, tags_vector);
    delete (int*)object;
    delete[] tags_array;
    delete add_tags_calls[call_id];
    add_tags_calls.erase(call_id);
  }

  void onDeleteTags(void* object, ModioResponse modio_response, int mod_id, ModioTag* tags_array, int tags_array_size)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::Tag> tags_vector;
    tags_vector.resize(tags_array_size);
    for(int i=0; i < tags_array_size; i++)
    {
      tags_vector[i].initialize(tags_array[i]);
    }

    delete_tags_calls[call_id]->callback(delete_tags_calls[call_id]->object, (const Response&)response, mod_id, tags_vector);

    delete (int*)object;
    delete[] tags_array;
    delete delete_tags_calls[call_id];
    delete_tags_calls.erase(call_id);
  }

  void Instance::getTags(void* object, u32 mod_id, const std::function<void(void* object, const modio::Response& response, std::vector<modio::Tag> tags)>& callback)
  {
    const struct GetTagsCall* get_tags_call = new GetTagsCall{object, callback};
    get_tags_calls[this->current_call_id] = (GetTagsCall*)get_tags_call;

    modioGetTags((void*)new int(this->current_call_id), mod_id, &onGetTags);

    this->current_call_id++;
  }

  void Instance::addTags(void* object, u32 mod_id, std::vector<std::string> tags, const std::function<void(void* object, const modio::Response& response, u32 mod_id, std::vector<modio::Tag> tags)>& callback)
  {
    const struct AddTagsCall* add_tags_call = new AddTagsCall{object, callback};
    add_tags_calls[this->current_call_id] = (AddTagsCall*)add_tags_call;

    int tags_array_size = tags.size();
    char** tags_array = new char*[tags_array_size];
    for(int i=0; i<tags_array_size; i++)
    {
      tags_array[i] = new char[tags[i].size() + 1];
      strcpy(tags_array[i],(char*)tags[i].c_str());
    }

    modioAddTags((void*)new int(this->current_call_id), mod_id, tags_array, tags_array_size, &onAddTags);
    this->current_call_id++;
  }

  void Instance::deleteTags(void* object, u32 mod_id, std::vector<std::string> tags, const std::function<void(void* object, const modio::Response& response, u32 mod_id, std::vector<modio::Tag> tags)>& callback)
  {
    const struct DeleteTagsCall* delete_tags_call = new DeleteTagsCall{object, callback};
    delete_tags_calls[this->current_call_id] = (DeleteTagsCall*)delete_tags_call;

    int tags_array_size = tags.size();
    char** tags_array = new char*[tags_array_size];
    for(int i=0; i<tags_array_size; i++)
    {
      tags_array[i] = new char[tags[i].size() + 1];
      strcpy(tags_array[i],(char*)tags[i].c_str());
    }

    modioDeleteTags((void*)new int(this->current_call_id), mod_id, tags_array, tags_array_size, &onDeleteTags);

    this->current_call_id++;
  }
}
