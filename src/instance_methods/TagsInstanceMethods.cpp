#include "ModIOInstance.h"

namespace modio
{
  struct GetTagsCall
  {
    void* object;
    const std::function<void(void* object, const ModioResponse& response, std::vector<std::string> tags)> callback;
  };

  struct AddTagsCall
  {
    void* object;
    const std::function<void(void* object, const ModioResponse& response, u32 mod_id, std::vector<std::string> tags)> callback;
  };

  struct DeleteTagsCall
  {
    void* object;
    const std::function<void(void* object, const ModioResponse& response, u32 mod_id, std::vector<std::string> tags)> callback;
  };

  std::map<int, GetTagsCall*> get_tags_calls;
  std::map<int, AddTagsCall*> add_tags_calls;
  std::map<int, DeleteTagsCall*> delete_tags_calls;

  void onGetTags(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size)
  {

  }

  void onAddTags(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size)
  {

  }

  void onDeleteTags(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size)
  {

  }

  void Instance::getTags(void* object, u32 mod_id, const std::function<void(void* object, const ModioResponse& response, std::vector<std::string> tags)>& callback)
  {
    const struct GetTagsCall* get_tags_call = new GetTagsCall{object, callback};
    get_tags_calls[this->current_call_id] = (GetTagsCall*)get_tags_call;

    modioGetTags((void*)new int(this->current_call_id), mod_id, &onGetTags);

    this->current_call_id++;
  }

  void Instance::addTags(void* object, u32 mod_id, std::vector<std::string> tags, const std::function<void(void* object, const ModioResponse& response, u32 mod_id, std::vector<std::string> tags)>& callback)
  {
    const struct AddTagsCall* add_tags_call = new AddTagsCall{object, callback};
    add_tags_calls[this->current_call_id] = (AddTagsCall*)add_tags_call;

    modioAddTags((void*)new int(this->current_call_id), mod_id, NULL, 0, &onAddTags);

    this->current_call_id++;
  }

  void Instance::deleteTags(void* object, u32 mod_id, std::vector<std::string> tags, const std::function<void(void* object, const ModioResponse& response, u32 mod_id, std::vector<std::string> tags)>& callback)
  {
    const struct DeleteTagsCall* delete_tags_call = new DeleteTagsCall{object, callback};
    delete_tags_calls[this->current_call_id] = (DeleteTagsCall*)delete_tags_call;

    modioDeleteTags((void*)new int(this->current_call_id), mod_id, NULL, 0, &onDeleteTags);

    this->current_call_id++;
  }
}
