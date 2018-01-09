#include "c/methods/ModMethods.h"

extern "C"
{
  struct GetModParams
  {
    void* object;
    void (*callback)(void* object, ModioResponse response, ModioMod mod);
  };

  struct GetModsParams
  {
    void* object;
    void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size);
  };

  struct AddModParams
  {
    void* object;
    void (*callback)(void* object, ModioResponse response, ModioMod mod);
  };

  struct DeleteModParams
  {
    void* object;
    u32 mod_id;
    void (*callback)(void* object, ModioResponse response, u32 mod_id);
  };

  struct CallbackParamReturnsId
  {
    void* object;
    u32 mod_id;
    void (*callback)(void* object, ModioResponse response, u32 mod_id);
  };

  std::map< u32,GetModParams* > get_mod_callbacks;
  std::map< u32,AddModParams* > add_mod_callback;
  std::map< u32,DeleteModParams* > delete_mod_callbacks;
  std::map< u32,GetModsParams* > get_mods_callbacks;
  std::map< u32,CallbackParamReturnsId* > return_id_callbacks;

  void modioOnGetMod(u32 call_number, u32 response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    ModioMod mod;
    modioInitMod(&mod, response_json);

    get_mod_callbacks[call_number]->callback(get_mod_callbacks[call_number]->object, response, mod);
    delete get_mod_callbacks[call_number];
    get_mod_callbacks.erase(call_number);

    modioFreeResponse(&response);
    modioFreeMod(&mod);
  }

  void modioOnGetMods(u32 call_number, u32 response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    if(response.code == 200)
    {
      u32 mods_size = (u32)response_json["data"].size();
      ModioMod* mods = new ModioMod[mods_size];
      for(u32 i=0; i<mods_size; i++)
      {
        modioInitMod(&mods[i], response_json["data"][i]);
      }
      get_mods_callbacks[call_number]->callback(get_mods_callbacks[call_number]->object, response, mods, mods_size);
      for(u32 i=0; i<mods_size; i++)
      {
        modioFreeMod(&mods[i]);
      }
      delete[] mods;
    }else
    {
      get_mods_callbacks[call_number]->callback(get_mods_callbacks[call_number]->object, response, NULL, 0);
    }
    delete get_mods_callbacks[call_number];
    get_mods_callbacks.erase(call_number);
    modioFreeResponse(&response);
  }

  void modioOnModAdded(u32 call_number, u32 response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    ModioMod mod;
    modioInitMod(&mod, response_json);

    add_mod_callback[call_number]->callback(add_mod_callback[call_number]->object, response, mod);
    delete add_mod_callback[call_number];
    add_mod_callback.erase(call_number);
  }

  void modioOnModDeleted(u32 call_number, u32 response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    delete_mod_callbacks[call_number]->callback(delete_mod_callbacks[call_number]->object, response, delete_mod_callbacks[call_number]->mod_id);
    delete delete_mod_callbacks[call_number];
    delete_mod_callbacks.erase(call_number);
  }

  void modioOnReturnIdCallback(u32 call_number, u32 response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    return_id_callbacks[call_number]->callback(return_id_callbacks[call_number]->object, response, return_id_callbacks[call_number]->mod_id);
    delete return_id_callbacks[call_number];
    return_id_callbacks.erase(call_number);
  }

  void modioGetMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioMod mod))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_mod_callbacks[call_number] = new GetModParams;
    get_mod_callbacks[call_number]->callback = callback;
    get_mod_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, headers, &modioOnGetMod);
  }

  void modioGetMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods?" + filter_string + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_mods_callbacks[call_number] = new GetModsParams;
    get_mods_callbacks[call_number]->callback = callback;
    get_mods_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, headers, &modioOnGetMods);
  }

  void modioGetUserMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/mods?" + filter_string + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_mods_callbacks[call_number] = new GetModsParams;
    get_mods_callbacks[call_number]->callback = callback;
    get_mods_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, headers, &modioOnGetMods);
  }

  void modioEditMod(void* object, u32 mod_id, ModioModEditor mod_editor, void (*callback)(void* object, ModioResponse response, ModioMod mod))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->callback = callback;
    add_mod_callback[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id);

    std::multimap<std::string,std::string> mod_params = modio::getModEditorCurlFormCopyContentsParams(&mod_editor);
    for(std::multimap<std::string,std::string>::iterator i = mod_params.begin(); i != mod_params.end(); i++)
    {
      if(i==mod_params.begin())
        url+="?";
      else
        url+="&";
      url+=(*i).first + "=" + (*i).second;
    }

    modio::curlwrapper::put(call_number, url, headers, mod_params, &modioOnModAdded);
  }

  void modioAddMod(void* object, ModioModCreator mod_creator, void (*callback)(void* object, ModioResponse response, ModioMod mod))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->callback = callback;
    add_mod_callback[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods";

    modio::curlwrapper::postForm(call_number, url, headers, modio::getModCreatorCurlFormCopyContentsParams(&mod_creator), modio::getModCreatorCurlFormFilesParams(&mod_creator), &modioOnModAdded);
  }

  void modioDeleteMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    delete_mod_callbacks[call_number] = new DeleteModParams;
    delete_mod_callbacks[call_number]->callback = callback;
    delete_mod_callbacks[call_number]->object = object;
    delete_mod_callbacks[call_number]->mod_id = mod_id;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id);

    modio::curlwrapper::deleteCall(call_number, url, headers, &modioOnModDeleted);
  }

  void modioSetUserModVote(void* object, u32 mod_id, bool vote_up, void (*callback)(void *object, ModioResponse response, u32 mod_id))
  {
    std::map<std::string, std::string> data;

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    u32 call_number = modio::curlwrapper::getCallCount();
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

    modio::curlwrapper::post(call_number, url, headers, data, &modioOnReturnIdCallback);
  }

  void modioSubscribeMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id))
  {
    std::map<std::string, std::string> data;

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    return_id_callbacks[call_number] = new CallbackParamReturnsId;
    return_id_callbacks[call_number]->mod_id = mod_id;
    return_id_callbacks[call_number]->callback = callback;
    return_id_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::post(call_number, url, headers, data, &modioOnReturnIdCallback);
  }

  void modioUnsubscribeMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    return_id_callbacks[call_number] = new CallbackParamReturnsId;
    return_id_callbacks[call_number]->mod_id = mod_id;
    return_id_callbacks[call_number]->callback = callback;
    return_id_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::deleteCall(call_number, url, headers, &modioOnReturnIdCallback);
  }
}
