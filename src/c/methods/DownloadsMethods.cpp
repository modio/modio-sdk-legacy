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
  std::string mod_path = modio::getInstalledModPath(mod_id);
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
  u32 i = 0;
  for (auto &queued_mod_download : modio::curlwrapper::getModDownloadQueue())
  {
    modioInitQueuedModDownload(&(download_queue[i]), modio::toJson(*queued_mod_download));
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
    modioInitQueuedModfileUpload(&(upload_queue[i]), modio::toJson(*queued_modfile_upload));
    i++;
  }
}

u32 modioGetModfileUploadQueueCount()
{
  return (u32)modio::curlwrapper::getModfileUploadQueue().size();
}

void modioGetAllInstalledMods(ModioInstalledMod *installed_mods)
{
  u32 i = 0;
  for(auto installed_mod_json : modio::installed_mods)
  {
    modioInitInstalledMod(&(installed_mods[i]), installed_mod_json);
    i++;
  }
}

u32 modioGetAllInstalledModsCount()
{
  return (u32)modio::installed_mods.size();
}

u32 modioGetModState(u32 mod_id)
{
  for(auto queued_mod_download : modio::curlwrapper::getModDownloadQueue())
  {
    if(queued_mod_download->mod_id == mod_id)
      return queued_mod_download->state;
  }

  for(auto installed_mod : modio::installed_mods)
  {
    if(modio::hasKey(installed_mod, "mod_id") && installed_mod["mod_id"] == mod_id)
      return MODIO_MOD_INSTALLED;
  }

  return MODIO_MOD_NOT_INSTALLED;
}
}
