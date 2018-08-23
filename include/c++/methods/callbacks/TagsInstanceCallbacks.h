
namespace modio
{
  struct GetModTagsCall
  {
    const std::function<void(const modio::Response& response, std::vector<modio::Tag> tags)> callback;
  };

  struct AddTagsCall
  {
    const std::function<void(const modio::Response& response)> callback;
  };

  struct DeleteTagsCall
  {
    const std::function<void(const modio::Response& response)> callback;
  };

  extern std::map<u32, GetModTagsCall*> get_mod_tags_calls;
  extern std::map<u32, AddTagsCall*> add_tags_calls;
  extern std::map<u32, DeleteTagsCall*> delete_tags_calls;

  void onGetModTags(void* object, ModioResponse modio_response, ModioTag* tags_array, u32 tags_array_size);
  void onAddTags(void* object, ModioResponse modio_response);
  void onDeleteTags(void* object, ModioResponse modio_response);
}
