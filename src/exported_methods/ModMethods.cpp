#include "exported_methods/ModMethods.h"

extern "C"
{
  struct GetModsParams
  {
    void* object;
    void (*callback)(void* object, ModioResponse response, ModioMod* mods, int mods_size);
  };

  struct AddModParams
  {
    void* object;
    void (*callback)(void* object, ModioResponse response, ModioMod* mod);
  };

  struct DeleteModParams
  {
    void* object;
    int mod_id;
    void (*callback)(void* object, ModioResponse response, int mod_id);
  };

  struct CallbackParamReturnsId
  {
    void* object;
    int mod_id;
    void (*callback)(void* object, ModioResponse response, int mod_id);
  };

  std::map< int,AddModParams* > add_mod_callback;
  std::map< int,DeleteModParams* > delete_mod_callbacks;
  std::map< int,GetModsParams* > get_mods_callbacks;
  std::map< int,CallbackParamReturnsId* > return_id_callbacks;

  void onGetMods(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    ModioMod* mods = NULL;
    int mods_size = 0;
    if(response.code == 200)
    {
      mods_size = (int)response_json["data"].size();
      mods = new ModioMod[mods_size];
      for(int i=0;i<mods_size;i++)
      {
        modioInitMod(&mods[i], response_json["data"][i]);
      }
    }
    get_mods_callbacks[call_number]->callback(get_mods_callbacks[call_number]->object, response, mods, mods_size);
    get_mods_callbacks.erase(call_number);
  }

  void modioGetMods(void* object, ModioFilter* filter, void (*callback)(void* object, ModioResponse response, ModioMod* mods, int mods_size))
  {
    std::string filter_string = modio::getFilterString(filter);
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods?" + filter_string + "&api_key=" + modio::API_KEY;

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_mods_callbacks[call_number] = new GetModsParams;
    get_mods_callbacks[call_number]->callback = callback;
    get_mods_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, headers, &onGetMods);
  }

  void onModAdded(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    ModioMod* mod = new ModioMod;
    modioInitMod(mod, response_json);

    add_mod_callback[call_number]->callback(add_mod_callback[call_number]->object, response, mod);
    add_mod_callback.erase(call_number);
  }

  void modioEditMod(void* object, int mod_id, ModioModHandler* mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod* mod))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->callback = callback;
    add_mod_callback[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id);

    std::multimap<std::string,std::string> mod_params = modio::getModfileCurlFormCopyContentsParams(mod_handler);
    for(std::multimap<std::string,std::string>::iterator i = mod_params.begin(); i != mod_params.end(); i++)
    {
      if(i==mod_params.begin())
        url+="?";
      else
        url+="&";
      url+=(*i).first + "=" + (*i).second;
    }

    modio::curlwrapper::put(call_number, url, headers, mod_params, &onModAdded);
  }

  void modioAddMod(void* object, ModioModHandler* mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod* mod))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->callback = callback;
    add_mod_callback[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods";

    modio::curlwrapper::postForm(call_number, url, headers, modio::getModfileCurlFormCopyContentsParams(mod_handler), modio::getModfileCurlFormFilesParams(mod_handler), &onModAdded);
  }

  void onModDeleted(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    delete_mod_callbacks[call_number]->callback(delete_mod_callbacks[call_number]->object, response, delete_mod_callbacks[call_number]->mod_id);
    delete_mod_callbacks.erase(call_number);
  }

  void modioDeleteMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    delete_mod_callbacks[call_number] = new DeleteModParams;
    delete_mod_callbacks[call_number]->callback = callback;
    delete_mod_callbacks[call_number]->object = object;
    delete_mod_callbacks[call_number]->mod_id = mod_id;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id);

    modio::curlwrapper::deleteCall(call_number, url, headers, &onModDeleted);
  }

  void onReturnIdCallback(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    return_id_callbacks[call_number]->callback(return_id_callbacks[call_number]->object, response, return_id_callbacks[call_number]->mod_id);
    return_id_callbacks.erase(call_number);
  }

  void modioSetUserModVote(void* object, int mod_id, bool vote_up, void (*callback)(void *object, ModioResponse response, int mod_id))
  {
    std::map<std::string, std::string> data;

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    return_id_callbacks[call_number] = new CallbackParamReturnsId;
    return_id_callbacks[call_number]->mod_id = mod_id;
    return_id_callbacks[call_number]->callback = callback;
    return_id_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/ratings";

    if(vote_up)
    {
      url += "?rating=1";
    }else
    {
      url += "?rating=-1";
    }

    modio::curlwrapper::post(call_number, url, headers, data, &onReturnIdCallback);
  }

  void modioSubscribeMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id))
  {
    std::map<std::string, std::string> data;

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    return_id_callbacks[call_number] = new CallbackParamReturnsId;
    return_id_callbacks[call_number]->mod_id = mod_id;
    return_id_callbacks[call_number]->callback = callback;
    return_id_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::post(call_number, url, headers, data, &onReturnIdCallback);
  }

  void modioUnsubscribeMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    return_id_callbacks[call_number] = new CallbackParamReturnsId;
    return_id_callbacks[call_number]->mod_id = mod_id;
    return_id_callbacks[call_number]->callback = callback;
    return_id_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::deleteCall(call_number, url, headers, &onReturnIdCallback);
  }
}
