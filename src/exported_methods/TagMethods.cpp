#include "exported_methods/TagMethods.h"

extern "C"
{
  struct EditTagsParams
  {
    int mod_id;
    void (*callback)(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size);
  };

  struct DeleteTagsParams
  {
    int mod_id;
    void (*callback)(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size);
  };

  struct GetTagsParams
  {
    int mod_id;
    void (*callback)(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size);
  };

  map< int, GetTagsParams* > get_tags_callbacks;
  map< int, EditTagsParams* > add_tags_callbacks;
  map< int, DeleteTagsParams* > delete_tags_callbacks;

  void onGetTags(int call_number, ModioResponse* response, json response_json)
  {
    vector<string> tags;
    ModioTag* tags_array = NULL;
    int tags_array_size = 0;
    if(response->code == 200)
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
        modio::writeLogLine(string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    get_tags_callbacks[call_number]->callback(response, get_tags_callbacks[call_number]->mod_id, tags_array, tags_array_size);
    get_tags_callbacks.erase(call_number);
  }

  void modioGetTags(int mod_id, void (*callback)(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size))
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/tags/";

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_tags_callbacks[call_number] = new GetTagsParams;
    get_tags_callbacks[call_number]->callback = callback;
    get_tags_callbacks[call_number]->mod_id = mod_id;

    std::thread get_tags_thread(modio::curlwrapper::get, call_number, url, headers, &onGetTags);
    get_tags_thread.detach();
  }

  void onTagsAdded(int call_number, ModioResponse* response, json response_json)
  {
    add_tags_callbacks[call_number]->callback(response, add_tags_callbacks[call_number]->mod_id, NULL, 0);
    add_tags_callbacks.erase(call_number);
  }

  void modioAddTags(int mod_id, char** tags_array, int tags_array_size, void (*callback)(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size))
  {
    map<string, string> data;

    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_tags_callbacks[call_number] = new EditTagsParams;
    add_tags_callbacks[call_number]->callback = callback;
    add_tags_callbacks[call_number]->mod_id = mod_id;

    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/tags";

    for(int i=0; i<(int)tags_array_size; i++)
    {
      if(i==0)
        url += "?";
      else
        url += "&";
      url += string("tags[]=") + tags_array[i];
    }

    std::thread add_tags_thread(modio::curlwrapper::post, call_number, url, headers, data, &onTagsAdded);
    add_tags_thread.detach();
  }

  void onTagsDeleted(int call_number, ModioResponse* response, json response_json)
  {
    delete_tags_callbacks[call_number]->callback(response, delete_tags_callbacks[call_number]->mod_id, NULL, 0);
    delete_tags_callbacks.erase(call_number);
  }

  void modioDeleteTags(int mod_id, char** tags_array, int tags_array_size, void (*callback)(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size))
  {
    map<string, string> data;

    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    delete_tags_callbacks[call_number] = new DeleteTagsParams;
    delete_tags_callbacks[call_number]->callback = callback;
    delete_tags_callbacks[call_number]->mod_id = mod_id;

    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/tags";

    for(int i=0; i<(int)tags_array_size; i++)
    {
      if(i==0)
        url += "?";
      else
        url += "&";
      url += string("tags[]=") + tags_array[i];
    }

    std::thread delete_tags_thread(modio::curlwrapper::deleteCall, call_number, url, headers, &onTagsDeleted);
    delete_tags_thread.detach();
  }
}
