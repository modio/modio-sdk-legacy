#include "c/methods/TagMethods.h"

extern "C"
{
  void modioGetTags(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id, ModioTag* tags_array, u32 tags_array_size))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/tags/";

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_tags_callbacks[call_number] = new GetTagsParams;
    get_tags_callbacks[call_number]->callback = callback;
    get_tags_callbacks[call_number]->mod_id = mod_id;
    get_tags_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, headers, &modioOnGetTags);
  }

  void modioAddTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response, u32 mod_id))
  {
    std::map<std::string, std::string> data;

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_tags_callbacks[call_number] = new EditTagsParams;
    add_tags_callbacks[call_number]->callback = callback;
    add_tags_callbacks[call_number]->mod_id = mod_id;
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

    modio::curlwrapper::post(call_number, url, headers, data, &modioOnTagsAdded);
  }

  void modioDeleteTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response, u32 mod_id))
  {
    std::map<std::string, std::string> data;

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    delete_tags_callbacks[call_number] = new DeleteTagsParams;
    delete_tags_callbacks[call_number]->callback = callback;
    delete_tags_callbacks[call_number]->mod_id = mod_id;
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

    modio::curlwrapper::deleteCall(call_number, url, headers, &modioOnTagsDeleted);
  }
}
