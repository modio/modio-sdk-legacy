#include "extern_c/methods/TagMethods.h"

extern "C"
{
  struct EditTagsParams
  {
    void* object;
    int mod_id;
    void (*callback)(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size);
  };

  struct DeleteTagsParams
  {
    void* object;
    int mod_id;
    void (*callback)(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size);
  };

  struct GetTagsParams
  {
    void* object;
    int mod_id;
    void (*callback)(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size);
  };

  std::map< int, GetTagsParams* > get_tags_callbacks;
  std::map< int, EditTagsParams* > add_tags_callbacks;
  std::map< int, DeleteTagsParams* > delete_tags_callbacks;

  void onGetTags(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    std::vector<std::string> tags;
    ModioTag* tags_array = NULL;
    int tags_array_size = 0;
    if(response.code == 200)
    {
      try
      {
        if(modio::hasKey(response_json, "data"))
        {
          tags_array_size = (int)response_json["data"].size();
          tags_array = new ModioTag[tags_array_size];
          for(int i=0; i<tags_array_size; i++)
          {
            modioInitTag(&(tags_array[i]), response_json["data"][i]);
          }
        }
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    get_tags_callbacks[call_number]->callback(get_tags_callbacks[call_number]->object, response, get_tags_callbacks[call_number]->mod_id, tags_array, tags_array_size);
    get_tags_callbacks.erase(call_number);
  }

  void modioGetTags(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/tags/";

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_tags_callbacks[call_number] = new GetTagsParams;
    get_tags_callbacks[call_number]->callback = callback;
    get_tags_callbacks[call_number]->mod_id = mod_id;
    get_tags_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, headers, &onGetTags);
  }

  void onTagsAdded(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    add_tags_callbacks[call_number]->callback(add_tags_callbacks[call_number]->object, response, add_tags_callbacks[call_number]->mod_id, NULL, 0);
    add_tags_callbacks.erase(call_number);
  }

  void modioAddTags(void* object, int mod_id, char** tags_array, int tags_array_size, void (*callback)(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size))
  {
    std::map<std::string, std::string> data;

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_tags_callbacks[call_number] = new EditTagsParams;
    add_tags_callbacks[call_number]->callback = callback;
    add_tags_callbacks[call_number]->mod_id = mod_id;
    add_tags_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/tags";

    for(int i=0; i<(int)tags_array_size; i++)
    {
      if(i==0)
        url += "?";
      else
        url += "&";
      url += std::string("tags[]=") + tags_array[i];
    }

    modio::curlwrapper::post(call_number, url, headers, data, &onTagsAdded);
  }

  void onTagsDeleted(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    delete_tags_callbacks[call_number]->callback(delete_tags_callbacks[call_number]->object, response, delete_tags_callbacks[call_number]->mod_id, NULL, 0);
    delete_tags_callbacks.erase(call_number);
  }

  void modioDeleteTags(void* object, int mod_id, char** tags_array, int tags_array_size, void (*callback)(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size))
  {
    std::map<std::string, std::string> data;

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    delete_tags_callbacks[call_number] = new DeleteTagsParams;
    delete_tags_callbacks[call_number]->callback = callback;
    delete_tags_callbacks[call_number]->mod_id = mod_id;
    delete_tags_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/tags";

    for(int i=0; i<(int)tags_array_size; i++)
    {
      if(i==0)
        url += "?";
      else
        url += "&";
      url += std::string("tags[]=") + tags_array[i];
    }

    modio::curlwrapper::deleteCall(call_number, url, headers, &onTagsDeleted);
  }
}
