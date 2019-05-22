#include "c/methods/TagMethods.h"

extern "C"
{
  void modioGetModTags(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioTag* tags_array, u32 tags_array_size))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/tags/";

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_mod_tags_callbacks[call_number] = new GetModTagsParams;
    get_mod_tags_callbacks[call_number]->callback = callback;
    get_mod_tags_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetModTags);
  }

  void modioAddModTags(void* object, u32 mod_id, char const* const* tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;

    u32 call_number = modio::curlwrapper::getCallNumber();

    add_mod_tags_callbacks[call_number] = new GenericRequestParams;
    add_mod_tags_callbacks[call_number]->callback = callback;
    add_mod_tags_callbacks[call_number]->object = object;

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

  void modioDeleteModTags(void* object, u32 mod_id, char const* const* tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;

    u32 call_number = modio::curlwrapper::getCallNumber();

    delete_mod_tags_callbacks[call_number] = new GenericRequestParams;
    delete_mod_tags_callbacks[call_number]->callback = callback;
    delete_mod_tags_callbacks[call_number]->object = object;

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
