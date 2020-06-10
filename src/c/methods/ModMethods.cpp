#include <map>                                                  // for map
#include <string>                                               // for string
#include <utility>                                              // for pair
#include "ModUtility.h"                                         // for getCa...
#include "dependencies/nlohmann/json.hpp"     // for json
#include "c/ModioC.h"                                // for u32
#include "c/creators/ModioFilterCreator.h"           // for getFi...
#include "c/creators/ModioModCreator.h"              // for getMo...
#include "c/creators/ModioModEditor.h"               // for getMo...
#include "Globals.h"               // for GAME_ID
#include "ModioUtility.h"          // for Gener...
#include "Utility.h"   // for toString
#include "wrappers/CurlWrapper.h"  // for getCa...
#include "c/methods/callbacks/ModCallbacks.h"                   // for AddMo...

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
    if(!callback)
    {
      modio::writeLogLine("NULL callback detected", MODIO_DEBUGLEVEL_ERROR);
      return;
    }

    std::string url_without_api_key = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods?" + (filter_string ? filter_string : "");
    std::string url = url_without_api_key + "&api_key=" + modio::API_KEY;

    for(auto get_all_mods_callbacks_iterator : get_all_mods_callbacks)
    {
      if(get_all_mods_callbacks_iterator.second->url == url_without_api_key)
      {
        modio::writeLogLine("Avoiding paralel call...", MODIO_DEBUGLEVEL_LOG);
        GetAllModsParams* existing_get_all_mods_params = get_all_mods_callbacks_iterator.second;
        existing_get_all_mods_params->callbacks.push_back(callback);
        existing_get_all_mods_params->objects.push_back(object);
        return;
      }
    }

    u32 call_number = modio::curlwrapper::getCallNumber();

    GetAllModsParams* new_get_all_mods_params = new GetAllModsParams;
    get_all_mods_callbacks[call_number] = new_get_all_mods_params;
    new_get_all_mods_params->url = url_without_api_key;
    new_get_all_mods_params->is_cache = false;
    new_get_all_mods_params->callbacks.push_back(callback);
    new_get_all_mods_params->objects.push_back(object);

    std::string cache_filename = modio::getCallFileFromCache(url_without_api_key, cache_max_age_seconds);
    if (cache_filename != "")
    {
      modio::writeLogLine("Cache file found: " + cache_filename, MODIO_DEBUGLEVEL_LOG);
      nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache/" + cache_filename);
      if (!cache_file_json.empty())
      {
        new_get_all_mods_params->is_cache = true;
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
    if(!modioIsLoggedIn())
    {
      modio::processLocalUnauthorizedRequestModParam(object, callback);
      return;
    }
    
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
