
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

  extern std::map<u32, GetTagsCall*> get_tags_calls;
  extern std::map<u32, AddTagsCall*> add_tags_calls;
  extern std::map<u32, DeleteTagsCall*> delete_tags_calls;

  void onGetTags(void* object, ModioResponse modio_response, u32 mod_id, ModioTag* tags_array, u32 tags_array_size);
  void onAddTags(void* object, ModioResponse modio_response, u32 mod_id);
  void onDeleteTags(void* object, ModioResponse modio_response, u32 mod_id);
}
