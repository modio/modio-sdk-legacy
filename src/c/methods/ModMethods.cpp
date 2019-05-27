#include "c/methods/ModMethods.h"

extern "C"
{
  void modioGetMod(void *object, u32 mod_id, void (*callback)(void *object, ModioResponse response, ModioMod mod))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_mod_callbacks[call_number] = new GetModParams;
    get_mod_callbacks[call_number]->callback = callback;
    get_mod_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetMod);
  }

  void modioGetAllModsFilterString(void* object, char const *filter_string, u32 cache_max_age_seconds, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods?" + (filter_string ? filter_string : "") + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_all_mods_callbacks[call_number] = new GetAllModsParams;
    get_all_mods_callbacks[call_number]->callback = callback;
    get_all_mods_callbacks[call_number]->object = object;
    get_all_mods_callbacks[call_number]->url = url;
    get_all_mods_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url, cache_max_age_seconds);
    if (cache_filename != "")
    {
      nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache/" + cache_filename);
      nlohmann::json empty_json = {};
      if (!cache_file_json.empty())
      {
        get_all_mods_callbacks[call_number]->is_cache = true;
        modioOnGetAllMods(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetAllMods);
  }

  void modioGetAllMods(void *object, ModioFilterCreator filter, void (*callback)(void *object, ModioResponse response, ModioMod mods[], u32 mods_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    modioGetAllModsFilterString(object, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }

  void modioEditMod(void *object, u32 mod_id, ModioModEditor mod_editor, void (*callback)(void *object, ModioResponse response, ModioMod mod))
  {
    u32 call_number = modio::curlwrapper::getCallNumber();

    add_mod_callbacks[call_number] = new AddModParams;
    add_mod_callbacks[call_number]->callback = callback;
    add_mod_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id);

    std::multimap<std::string, std::string> mod_params = modio::getModEditorCurlFormCopyContentsParams(&mod_editor);
    for (std::multimap<std::string, std::string>::iterator i = mod_params.begin(); i != mod_params.end(); i++)
    {
      if (i == mod_params.begin())
        url += "?";
      else
        url += "&";
      url += (*i).first + "=" + (*i).second;
    }

    modio::curlwrapper::put(call_number, url, modio::getHeaders(), mod_params, &modioOnModAdded);
  }

  void modioAddMod(void *object, ModioModCreator mod_creator, void (*callback)(void *object, ModioResponse response, ModioMod mod))
  {
    u32 call_number = modio::curlwrapper::getCallNumber();

    add_mod_callbacks[call_number] = new AddModParams;
    add_mod_callbacks[call_number]->callback = callback;
    add_mod_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods";
    modio::curlwrapper::postForm(call_number, url, modio::getHeaders(), modio::getModCreatorCurlFormCopyContentsParams(&mod_creator), modio::getModCreatorCurlFormFilesParams(&mod_creator), &modioOnModAdded);
  }

  void modioDeleteMod(void *object, u32 mod_id, void (*callback)(void *object, ModioResponse response))
  {
    std::map<std::string, std::string> data;
    u32 call_number = modio::curlwrapper::getCallNumber();

    delete_mod_callbacks[call_number] = new GenericRequestParams;
    delete_mod_callbacks[call_number]->callback = callback;
    delete_mod_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id);

    modio::curlwrapper::deleteCall(call_number, url, modio::getHeaders(), data, &modioOnModDeleted);
  }
}
