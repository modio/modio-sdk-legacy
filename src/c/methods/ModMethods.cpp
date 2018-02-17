#include "c/methods/ModMethods.h"

extern "C"
{
  void modioGetMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioMod mod))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_mod_callbacks[call_number] = new GetModParams;
    get_mod_callbacks[call_number]->callback = callback;
    get_mod_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetMod);
  }

  void modioGetMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods?" + filter_string + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_mods_callbacks[call_number] = new GetModsParams;
    get_mods_callbacks[call_number]->callback = callback;
    get_mods_callbacks[call_number]->object = object;
    get_mods_callbacks[call_number]->url = url;
    get_mods_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url, filter.cache_max_age_seconds);
    if(cache_filename != "")
    {
      std::ifstream cache_file(modio::getModIODirectory() + "cache/" + cache_filename);
      json cache_file_json;
      if(cache_file.is_open())
      {
        cache_file >> cache_file_json;
        get_mods_callbacks[call_number]->is_cache = true;
        modioOnGetMods(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetMods);
  }

  void modioEditMod(void* object, u32 mod_id, ModioModEditor mod_editor, void (*callback)(void* object, ModioResponse response, ModioMod mod))
  {
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

    modio::curlwrapper::put(call_number, url, modio::getHeaders(), mod_params, &modioOnModAdded);
  }

  void modioAddMod(void* object, ModioModCreator mod_creator, void (*callback)(void* object, ModioResponse response, ModioMod mod))
  {
    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->callback = callback;
    add_mod_callback[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods";

    modio::curlwrapper::postForm(call_number, url, modio::getHeaders(), modio::getModCreatorCurlFormCopyContentsParams(&mod_creator), modio::getModCreatorCurlFormFilesParams(&mod_creator), &modioOnModAdded);
  }

  void modioDeleteMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id))
  {
    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    delete_mod_callbacks[call_number] = new DeleteModParams;
    delete_mod_callbacks[call_number]->callback = callback;
    delete_mod_callbacks[call_number]->object = object;
    delete_mod_callbacks[call_number]->mod_id = mod_id;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id);

    modio::curlwrapper::deleteCall(call_number, url, modio::getHeaders(), &modioOnModDeleted);
  }

  void modioInstallMod(void* object, u32 mod_id, char* destination_path, void (*callback)(void* object, ModioResponse response))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_install_mod_callbacks[call_number] = new GetInstallModParams;
    get_install_mod_callbacks[call_number]->object = object;
    get_install_mod_callbacks[call_number]->mod_id = mod_id;
    get_install_mod_callbacks[call_number]->destination_path = modio::addSlashIfNeeded(destination_path);
    get_install_mod_callbacks[call_number]->callback = callback;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &onGetInstallMod);
  }

  double modioGetModfileDownloadPercentage(u32 modfile_id)
  {
    if(install_mod_callbacks.find(modio::curlwrapper::getOngoingCall()) != install_mod_callbacks.end())
    {
      InstallModParams* install_modfile_params = install_mod_callbacks[modio::curlwrapper::getOngoingCall()];

      if(install_modfile_params->mod_id == modfile_id)
      {
        modio::CurrentDownloadInfo current_download_info = modio::curlwrapper::getCurrentDownloadInfo();

        if(current_download_info.download_progress == 0)
          return 0;
        double result = current_download_info.download_progress;
        result /= current_download_info.download_total;
        return result * 100;
      }
    }
    return -1;
  }
}
