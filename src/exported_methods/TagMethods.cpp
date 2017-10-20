#include "exported_methods/TagMethods.h"

namespace modio
{
  struct EditTagsParams
  {
    ModioMod* mod;
    function<void(ModioResponse* response, ModioMod*)> callback;
  };

  struct DeleteTagsParams
  {
    ModioMod* mod;
    function<void(ModioResponse* response, ModioMod*)> callback;
  };

  struct GetTagsParams
  {
    ModioMod* mod;
    function<void(ModioResponse* response, ModioMod*, vector<string>)> callback;
  };

  map< int, GetTagsParams* > get_tags_callbacks;
  map< int, EditTagsParams* > add_tags_callbacks;
  map< int, DeleteTagsParams* > delete_tags_callbacks;

  void onGetTags(int call_number, ModioResponse* response, json response_json)
  {
    vector<string> tags;

    if(response->code == 200)
    {
      for(int i=0;i<(int)response_json["data"].size();i++)
      {
        tags.push_back(response_json["data"][i]["tag"]);
      }
    }

    get_tags_callbacks[call_number]->callback(response, get_tags_callbacks[call_number]->mod, tags);
    get_tags_callbacks.erase(call_number);
  }

  void getTags(ModioMod* mod, function<void(ModioResponse* response, ModioMod* mod, vector<string> tags)> callback)
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    string url = MODIO_URL + MODIO_VERSION_PATH + "games/" + toString(modio::GAME_ID) + "/mods/" + toString(mod->id) + "/tags/";

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    get_tags_callbacks[call_number] = new GetTagsParams;
    get_tags_callbacks[call_number]->callback = callback;
    get_tags_callbacks[call_number]->mod = mod;

    std::thread get_tags_thread(curlwrapper::get, call_number, url, headers, &onGetTags);
    get_tags_thread.detach();
  }

  void onTagsAdded(int call_number, ModioResponse* response, json response_json)
  {
    add_tags_callbacks[call_number]->callback(response, add_tags_callbacks[call_number]->mod);
    add_tags_callbacks.erase(call_number);
  }

  void MODIO_DLL addTags(ModioMod* mod, vector<string> tags, function<void(ModioResponse* response, ModioMod* mod)> callback)
  {
    map<string, string> data;

    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    add_tags_callbacks[call_number] = new EditTagsParams;
    add_tags_callbacks[call_number]->callback = callback;
    add_tags_callbacks[call_number]->mod = mod;

    string url = MODIO_URL + MODIO_VERSION_PATH + "games/" + toString(modio::GAME_ID) + "/mods/" + toString(mod->id) + "/tags";

    for(int i=0; i<(int)tags.size(); i++)
    {
      if(i==0)
        url += "?";
      else
        url += "&";
      url += "tags[]=" + tags[i];
    }

    std::thread add_tags_thread(curlwrapper::post, call_number, url, headers, data, &onTagsAdded);
    add_tags_thread.detach();
  }

  void onTagsDeleted(int call_number, ModioResponse* response, json response_json)
  {
    delete_tags_callbacks[call_number]->callback(response, delete_tags_callbacks[call_number]->mod);
    delete_tags_callbacks.erase(call_number);
  }

  void MODIO_DLL deleteTags(ModioMod* mod, vector<string> tags, function<void(ModioResponse* response, ModioMod* mod)> callback)
  {
    map<string, string> data;

    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    delete_tags_callbacks[call_number] = new DeleteTagsParams;
    delete_tags_callbacks[call_number]->callback = callback;
    delete_tags_callbacks[call_number]->mod = mod;

    string url = MODIO_URL + MODIO_VERSION_PATH + "games/" + toString(modio::GAME_ID) + "/mods/" + toString(mod->id) + "/tags";

    for(int i=0; i<(int)tags.size(); i++)
    {
      if(i==0)
        url += "?";
      else
        url += "&";
      url += "tags[]=" + tags[i];
    }

    std::thread delete_tags_thread(curlwrapper::deleteCall, call_number, url, headers, &onTagsDeleted);
    delete_tags_thread.detach();
  }
}
