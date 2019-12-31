#include <stddef.h>
#include <list>
#include <string>
#include <vector>
#include "ModUtility.h"
#include "Globals.h"
#include "c++/schemas/QueuedModDownload.h"
#include "c++/schemas/QueuedModfileUpload.h"
#include "ModioUtility.h"
#include "Utility.h"
#include "c/ModioC.h"
#include "dependencies/nlohmann/json.hpp"
#include "wrappers/CurlWrapper.h"
#include "c/schemas/ModioInstalledMod.h"
#include "c/schemas/ModioQueuedModDownload.h"
#include "c/schemas/ModioQueuedModfileUpload.h"
#include "wrappers/CurlUtility.h"

extern "C" {
void modioDownloadMod(u32 mod_id)
{
  std::vector<u32> mod_ids;
  mod_ids.push_back(mod_id);
  modio::addModsToDownloadQueue(mod_ids);
}

void modioInstallDownloadedMods()
{
  modio::installDownloadedMods();
}

bool modioUninstallMod(u32 mod_id)
{
  modio::writeLogLine("Uninstalling mod. Mod id: " + modio::toString(mod_id), MODIO_DEBUGLEVEL_LOG);
  std::string mod_path = modio::getInstalledModPath(mod_id);
  bool result = mod_path != "" && modio::checkIfModIsStillInstalled(mod_path, mod_id) && modio::removeDirectory(mod_path);
  modio::current_user_subscriptions.erase(mod_id);
  modio::updateInstalledModsJson();
  return result;
}

void modioPauseDownloads()
{
  modio::curlwrapper::pauseModDownloads();
}

void MODIO_DLL modioCancelModDownload(u32 mod_id)
{
  bool mod_found = false;
  for (auto &queued_mod_download : modio::curlwrapper::g_mod_download_queue)
  {
    if (queued_mod_download->mod_id == mod_id)
    {
      if(queued_mod_download->state == MODIO_MOD_STARTING_DOWNLOAD
          && queued_mod_download->state == MODIO_MOD_DOWNLOADING
          && queued_mod_download->state == MODIO_MOD_PAUSING
          && queued_mod_download->state == MODIO_PRIORITIZING_OTHER_DOWNLOAD
          )
      {
        modio::writeLogLine("Mod id: " + modio::toString(mod_id) + " is being downloaded, cancelling download...", MODIO_DEBUGLEVEL_LOG);
        queued_mod_download->state = MODIO_MOD_CANCELLING;
        mod_found = true;
      } else
      {
        modio::writeLogLine("Mod id: " + modio::toString(mod_id) + " was removed from the download queue.", MODIO_DEBUGLEVEL_LOG);
        modio::curlwrapper::g_mod_download_queue.remove(queued_mod_download);
        delete queued_mod_download;
        mod_found = true;
        break;
      }
    }
  }
  if(mod_found)
    modio::writeLogLine("Mod id: " + modio::toString(mod_id) + " was not found on the dowload queue.", MODIO_DEBUGLEVEL_WARNING);
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

void modioGetInstalledMod(u32 mod_id, ModioInstalledMod *installed_mod)
{
  u32 i = 0;
  for(auto installed_mod_json : modio::installed_mods)
  {
		if (modio::hasKey(installed_mod_json, "mod_id")
        && mod_id == installed_mod_json["mod_id"])
    {
      modioInitInstalledMod(installed_mod, installed_mod_json);
      return;
    }
    i++;
  }
  nlohmann::json empty_json;
  modioInitInstalledMod(installed_mod, empty_json);
}

u32 modioGetAllInstalledModsCount()
{
  return (u32)modio::installed_mods.size();
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

u32 modioGetAllDownloadedModsCount()
{
  return (u32)modio::downloaded_mods.size();
}

void modioGetAllDownloadedMods(u32* downloaded_mods)
{
  for(size_t i=0; i<(u32)modio::downloaded_mods.size(); i++)
  {
    downloaded_mods[i] = modio::downloaded_mods[i];
  }
}

u32 modioGetModState(u32 mod_id)
{
  for(auto& queued_mod_download : modio::curlwrapper::getModDownloadQueue())
  {
    if(queued_mod_download->mod_id == mod_id)
      return queued_mod_download->state;
  }

  for(auto& downloaded_mod : modio::downloaded_mods)
  {
    if(downloaded_mod == mod_id)
      return MODIO_MOD_DOWNLOADED;
  }

  for(auto& installed_mod : modio::installed_mods)
  {
    if(modio::hasKey(installed_mod, "mod_id") && installed_mod["mod_id"] == mod_id)
      return MODIO_MOD_INSTALLED;
  }

  return MODIO_MOD_NOT_INSTALLED;
}
}
