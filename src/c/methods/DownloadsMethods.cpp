#include "c/methods/DownloadsMethods.h"

extern "C"
{
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

  bool modioUninstallModfile(u32 modfile_id)
  {
    modio::updateInstalledModsJson();
    std::string modfile_path = modio::getInstalledModfilePath(modfile_id);

    bool result = modfile_path != "" && modio::checkIfModIsStillInstalled(modfile_path, modfile_id) && modio::removeDirectory(modfile_path);
    modio::updateInstalledModsJson();
    return result;
  }

  u32 modioGetInstalledModfilesCount()
  {
    std::ifstream installed_mods_file(modio::getModIODirectory() + "installed_mods.json");
    if(installed_mods_file.is_open())
    {
      json installed_mods_json;
      try
      {
        installed_mods_file >> installed_mods_json;
        installed_mods_json = installed_mods_json["mods"];
        return (u32)installed_mods_json.size();
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    return 0;
  }

  u32 modioGetInstalledModfileId(u32 index)
  {
    std::ifstream installed_mods_file(modio::getModIODirectory() + "installed_mods.json");
    if(installed_mods_file.is_open())
    {
      json installed_mods_json;
      try
      {
        installed_mods_file >> installed_mods_json;
        if(index >= installed_mods_json["mods"].size())
        {
          return 0;
        }
        return installed_mods_json["mods"][index]["modfile_id"];
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    return 0;
  }

  u32 modioGetModfileState(u32 modfile_id)
  {
    if(modioGetModfileDownloadPercentage(modfile_id) != -1)
    {
      return MODIO_MODFILE_INSTALLING;
    }
    std::ifstream installed_mods_file(modio::getModIODirectory() + "installed_mods.json");
    if(installed_mods_file.is_open())
    {
      json installed_mods_json;
      try
      {
        installed_mods_file >> installed_mods_json;
        for(u32 i=0; i<installed_mods_json["mods"].size(); i++)
        {
          if(modfile_id == installed_mods_json["mods"][i]["id"])
          {
            return MODIO_MODFILE_INSTALLED;
          }
        }
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    return MODIO_MODFILE_NOT_INSTALLED;
  }

  void modioPauseCurrentDownload()
  {
    modio::curlwrapper::pauseCurrentDownload();
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
