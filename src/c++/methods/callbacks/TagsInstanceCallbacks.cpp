#include "c++/ModIOInstance.h"

namespace modio
{
  std::map<u32, GetTagsCall*> get_tags_calls;
  std::map<u32, AddTagsCall*> add_tags_calls;
  std::map<u32, DeleteTagsCall*> delete_tags_calls;

  void onGetTags(void* object, ModioResponse modio_response, ModioTag* tags_array, u32 tags_array_size)
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

  void onAddTags(void* object, ModioResponse modio_response)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    add_tags_calls[call_id]->callback((const Response&)response);
    delete add_tags_calls[call_id];
    delete (u32*)object;
    add_tags_calls.erase(call_id);
  }

  void onDeleteTags(void* object, ModioResponse modio_response, u32 mod_id)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    delete_tags_calls[call_id]->callback((const Response&)response);
    delete delete_tags_calls[call_id];
    delete (u32*)object;
    delete_tags_calls.erase(call_id);
  }
}
