#include "c/methods/DownloadsMethods.h"

extern "C" {
void modioInstallMod(void *object, u32 mod_id)
{
  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "?api_key=" + modio::API_KEY;

  u32 call_number = modio::curlwrapper::getCallNumber();

  get_install_mod_callbacks[call_number] = new GetInstallModParams;
  get_install_mod_callbacks[call_number]->object = object;
  get_install_mod_callbacks[call_number]->mod_id = mod_id;
  get_install_mod_callbacks[call_number]->destination_path = modio::getModIODirectory() + "mods/" + modio::toString(mod_id);

  modio::curlwrapper::get(call_number, url, modio::getHeaders(), &onGetInstallMod);
}

bool modioUninstallModfile(u32 modfile_id)
{
  modio::updateInstalledModsJson();
  std::string modfile_path = modio::getInstalledModfilePath(modfile_id);

  bool result = modfile_path != "" && modio::checkIfModfileIsStillInstalled(modfile_path, modfile_id) && modio::removeDirectory(modfile_path);
  modio::updateInstalledModsJson();
  return result;
}

bool modioUninstallMod(u32 mod_id)
{
  modio::updateInstalledModsJson();
  std::string mod_path = modio::getInstalledModPath(mod_id);

  bool result = mod_path != "" && modio::checkIfModIsStillInstalled(mod_path, mod_id) && modio::removeDirectory(mod_path);
  modio::updateInstalledModsJson();
  return result;
}

u32 modioGetInstalledModfilesCount()
{
  json installed_mods_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");
  if (!installed_mods_json.empty())
  {
    return (u32)installed_mods_json["mods"].size();
  }
  return 0;
}

u32 modioGetInstalledModfileId(u32 index)
{
  json installed_mods_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");
  if (!installed_mods_json.empty())
  {
    if (index >= installed_mods_json["mods"].size())
    {
      return 0;
    }
    return installed_mods_json["mods"][index]["modfile_id"];
  }
  return 0;
}

u32 modioGetModfileState(u32 modfile_id)
{
  json installed_mods_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");

  if (!installed_mods_json.empty())
  {
    for (u32 i = 0; i < installed_mods_json["mods"].size(); i++)
    {
      if (modfile_id == installed_mods_json["mods"][i]["id"])
      {
        return MODIO_MODFILE_INSTALLED;
      }
    }
  }
  return MODIO_MODFILE_NOT_INSTALLED;
}

void modioPauseDownloads()
{
  modio::curlwrapper::pauseModDownloads();
}

void modioResumeDownloads()
{
  modio::curlwrapper::resumeModDownloads();
}

void modioGetInstalledMods(ModioInstalledMod *installed_mods)
{
  json installed_mod_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");
  if (!installed_mod_json.empty())
  {
    for (u32 i = 0; i < installed_mod_json["mods"].size(); i++)
    {
      modioInitInstalledMod(&(installed_mods[i]), installed_mod_json["mods"][i]);
    }
  }
}

u32 modioGetInstalledModsSize()
{
  json installed_mod_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");
  if (modio::hasKey(installed_mod_json, "mod"))
  {
    return (u32)installed_mod_json["mods"].size();
  }
  return 0;
}

void modioSetDownloadListener(void (*callback)(u32 response_code, u32 mod_id))
{
  modio::download_callback = callback;
}
}
