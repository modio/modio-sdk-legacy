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
    ModioMod* mod;
    void (*callback)(void* object, ModioResponse response, ModioMod* mod);
  };

  struct CallbackParamReturnsId
  {
    void* object;
    int mod_id;
    void (*callback)(void* object, ModioResponse response, int mod_id);
  };

  map< int,AddModParams* > add_mod_callback;
  map< int,DeleteModParams* > delete_mod_callbacks;
  map< int,GetModsParams* > get_mods_callbacks;
  map< int,CallbackParamReturnsId* > return_id_callbacks;

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
    string filter_string = modio::getFilterString(filter);
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods?" + filter_string + "&api_key=" + modio::API_KEY;

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
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->callback = callback;
    add_mod_callback[call_number]->object = object;

    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id);

    modio::curlwrapper::put(call_number, url, headers, modio::getModfileCurlFormCopyContentsParams(mod_handler), &onModAdded);
  }

  void modioAddMod(void* object, ModioModHandler* mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod* mod))
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->callback = callback;
    add_mod_callback[call_number]->object = object;

    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods";

    modio::curlwrapper::postForm(call_number, url, headers, modio::getModfileCurlFormCopyContentsParams(mod_handler), modio::getModfileCurlFormFilesParams(mod_handler), &onModAdded);
  }

  void onModDeleted(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    ModioMod* mod = new ModioMod;
    modioInitMod(mod, response_json);
    delete_mod_callbacks[call_number]->callback(delete_mod_callbacks[call_number]->object, response, mod);
    delete_mod_callbacks.erase(call_number);
  }

  void modioDeleteMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, ModioMod* mod))
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    delete_mod_callbacks[call_number] = new DeleteModParams;
    delete_mod_callbacks[call_number]->callback = callback;
    delete_mod_callbacks[call_number]->object = object;

    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id);

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
    map<string, string> data;

    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    return_id_callbacks[call_number] = new CallbackParamReturnsId;
    return_id_callbacks[call_number]->mod_id = mod_id;
    return_id_callbacks[call_number]->callback = callback;
    return_id_callbacks[call_number]->object = object;

    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/ratings";

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
    map<string, string> data;

    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    return_id_callbacks[call_number] = new CallbackParamReturnsId;
    return_id_callbacks[call_number]->mod_id = mod_id;
    return_id_callbacks[call_number]->callback = callback;
    return_id_callbacks[call_number]->object = object;

    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::post(call_number, url, headers, data, &onReturnIdCallback);
  }

  void modioUnsubscribeMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id))
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    return_id_callbacks[call_number] = new CallbackParamReturnsId;
    return_id_callbacks[call_number]->mod_id = mod_id;
    return_id_callbacks[call_number]->callback = callback;
    return_id_callbacks[call_number]->object = object;

    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::deleteCall(call_number, url, headers, &onReturnIdCallback);
  }
}
