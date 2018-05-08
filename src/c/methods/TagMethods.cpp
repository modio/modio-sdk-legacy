#include "c/methods/TagMethods.h"

extern "C"
{
  void modioGetTags(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioTag* tags_array, u32 tags_array_size))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/tags/";

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_tags_callbacks[call_number] = new GetTagsParams;
    get_tags_callbacks[call_number]->callback = callback;
    get_tags_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetTags);
  }

  void modioAddTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;

    u32 call_number = modio::curlwrapper::getCallNumber();

    add_tags_callbacks[call_number] = new EditTagsParams;
    add_tags_callbacks[call_number]->callback = callback;
    add_tags_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/tags";

    for(u32 i=0; i<tags_array_size; i++)
    {
      if(i==0)
        url += "?";
      else
        url += "&";
      url += std::string("tags[]=") + tags_array[i];
    }

    modio::curlwrapper::post(call_number, url, modio::getUrlEncodedHeaders(), data, &modioOnTagsAdded);
  }

  void modioDeleteTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;

    u32 call_number = modio::curlwrapper::getCallNumber();

    delete_tags_callbacks[call_number] = new DeleteTagsParams;
    delete_tags_callbacks[call_number]->callback = callback;
    delete_tags_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/tags";

    for(u32 i=0; i<tags_array_size; i++)
    {
      if(i==0)
        url += "?";
      else
        url += "&";
      url += std::string("tags[]=") + tags_array[i];
    }

    modio::curlwrapper::deleteCall(call_number, url, modio::getUrlEncodedHeaders(), data, &modioOnTagsDeleted);
  }
}
