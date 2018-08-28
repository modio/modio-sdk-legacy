#include "c/methods/DownloadsMethods.h"

extern "C" {
void modioInstallMod(u32 mod_id)
{
  std::vector<u32> mod_ids;
  mod_ids.push_back(mod_id);
  modio::addModsToDownloadQueue(mod_ids);
}

bool modioUninstallMod(u32 mod_id)
{
  modio::updateInstalledModsJson();
  std::string mod_path = modio::getAllInstalledModPath(mod_id);

  bool result = mod_path != "" && modio::checkIfModIsStillInstalled(mod_path, mod_id) && modio::removeDirectory(mod_path);
  modio::updateInstalledModsJson();
  return result;
}

void modioPauseDownloads()
{
  modio::curlwrapper::pauseModDownloads();
}

void modioResumeDownloads()
{
  modio::curlwrapper::resumeModDownloads();
}

void modioPrioritizeModDownload(u32 mod_id)
{
  modio::curlwrapper::prioritizeModDownload(mod_id);
}

void modioSetDownloadListener(void (*callback)(u32 response_code, u32 mod_id))
{
  modio::download_callback = callback;
}

void modioSetUploadListener(void (*callback)(u32 response_code, u32 mod_id))
{
  modio::upload_callback = callback;
}

void modioGetModDownloadQueue(ModioQueuedModDownload* download_queue)
{
  std::list<modio::QueuedModDownload *> mod_download_queue = modio::curlwrapper::getModDownloadQueue();
  u32 i = 0;
  for (auto &queued_mod_download : mod_download_queue)
  {
    modioInitQueuedModDownload(&(download_queue[i]), queued_mod_download->toJson());
    i++;
  }
}

u32 modioGetModDownloadQueueCount()
{
  return (u32)modio::curlwrapper::getModDownloadQueue().size();
}

void modioGetModfileUploadQueue(ModioQueuedModfileUpload* upload_queue)
{
  std::list<modio::QueuedModfileUpload *> modfile_upload_queue = modio::curlwrapper::getModfileUploadQueue();
  u32 i = 0;
  for (auto &queued_modfile_upload : modfile_upload_queue)
  {
    modioInitQueuedModfileUpload(&(upload_queue[i]), queued_modfile_upload->toJson());
    i++;
  }
}

u32 modioGetModfileUploadQueueCount()
{
  return (u32)modio::curlwrapper::getModfileUploadQueue().size();
}

bool modioGetAllInstalledModById(u32 mod_id, ModioInstalledMod *installed_mod)
{
  nlohmann::json installed_mod_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");
  if (!installed_mod_json.empty())
  {
    for (u32 i = 0; i < installed_mod_json["mods"].size(); i++)
    {
      if(modio::hasKey(installed_mod_json["mods"][i], "mod_id"), installed_mod_json["mods"][i]["mod_id"] == mod_id)
      {
        modioInitInstalledMod(installed_mod, installed_mod_json["mods"][i]);
        return true;
      }
    }
  }
  return false;
}

void modioGetAllInstalledMods(ModioInstalledMod *installed_mods)
{
  nlohmann::json installed_mod_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");
  if (!installed_mod_json.empty())
  {
    for (u32 i = 0; i < installed_mod_json["mods"].size(); i++)
    {
      modioInitInstalledMod(&(installed_mods[i]), installed_mod_json["mods"][i]);
    }
  }
}

u32 modioGetAllInstalledModsCount()
{
  nlohmann::json installed_mod_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");
  if (modio::hasKey(installed_mod_json, "mods"))
  {
    return (u32)installed_mod_json["mods"].size();
  }
  return 0;
}

u32 modioGetModState(u32 mod_id)
{
  u32 queue_size = modioGetModDownloadQueueCount();
  ModioQueuedModDownload* download_queue = new ModioQueuedModDownload[queue_size];
  modioGetModDownloadQueue(download_queue);
  
  for(u32 i = 0; i<queue_size; i++)
    if(download_queue[i].mod_id == mod_id)
      return download_queue[i].state;
  
  delete[] download_queue;

  u32 installed_mods_size = modioGetAllInstalledModsCount();
  ModioInstalledMod* installed_mods = new ModioInstalledMod[installed_mods_size];
  modioGetAllInstalledMods(installed_mods);
  
  for(u32 i = 0; i<installed_mods_size; i++)
    if(installed_mods[i].mod_id == mod_id)
      return MODIO_MOD_INSTALLED;

  return MODIO_MOD_NOT_INSTALLED;
}
}
