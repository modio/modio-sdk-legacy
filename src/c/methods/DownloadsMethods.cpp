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

void modioCancelModDownload(u32 mod_id)
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
  return (u32)modio::g_downloaded_mods.size();
}

void modioGetAllDownloadedMods(u32* downloaded_mods)
{
  u32 i = 0;
  for (auto &downloaded_mod : modio::g_downloaded_mods)
  {
    if(modio::hasKey(downloaded_mod, "mod") &&
        modio::hasKey(downloaded_mod["mod"], "id"))
    {
      downloaded_mods[i] = downloaded_mod["mod"]["id"];
      i++;
    }
  }
}

u32 modioGetModState(u32 mod_id)
{
  for(auto& queued_mod_download : modio::curlwrapper::getModDownloadQueue())
  {
    if(queued_mod_download->mod_id == mod_id)
      return queued_mod_download->state;
  }

  for (auto &downloaded_mod : modio::g_downloaded_mods)
  {
    if(modio::hasKey(downloaded_mod, "mod") &&
        modio::hasKey(downloaded_mod["mod"], "id") &&
        downloaded_mod["mod"]["id"] == mod_id)
    {
      return MODIO_MOD_DOWNLOADED;
    }
  }

  for(auto& installed_mod : modio::installed_mods)
  {
    if(modio::hasKey(installed_mod, "mod_id") && installed_mod["mod_id"] == mod_id)
      return MODIO_MOD_INSTALLED;
  }

  return MODIO_MOD_NOT_INSTALLED;
}

void onModioCheckIfModsAreUpdate(void *object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  modio::writeLogLine("onModioCheckIfModsAreUpdate was returned", MODIO_DEBUGLEVEL_ERROR);
  if (response.code == 200)
  {
    std::vector<u32> mod_ids_that_need_update;
    for (u32 i = 0; i < mods_size; i++)
    {
      ModioInstalledMod installed_mod;
      modioGetInstalledMod(mods[i].id, &installed_mod);
      if (installed_mod.mod_id != 0)
      {
        if(installed_mod.date_updated < mods[i].date_updated)
        {
          modio::writeLogLine("The following installed mod needs an update: " + modio::toString(mods[i].id), MODIO_DEBUGLEVEL_LOG);
          mod_ids_that_need_update.push_back(mods[i].id);
          modio::writeLogLine("Mod will be added to the download queue.", MODIO_DEBUGLEVEL_LOG);
        }
      }
      else
      {
        modio::writeLogLine("Installed mod not found: " + modio::toString(mods[i].id), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    modio::addModsToDownloadQueue(mod_ids_that_need_update);
  }else
  {
    modio::writeLogLine("Could not retrieve mods data error code: " + modio::toString(response.code), MODIO_DEBUGLEVEL_ERROR);
  }
  modio::writeLogLine("onModioCheckIfModsAreUpdate finished", MODIO_DEBUGLEVEL_LOG);
}

void modioCheckIfModsAreUpdated(void* object, u32 const* mod_id_array, u32 mod_id_array_size, void(*callback)(void* object, ModioResponse response, bool mods_are_updated))
{
  modio::writeLogLine("Checking is mods are updated...", MODIO_DEBUGLEVEL_ERROR);
  int i = 0;
  while(i < mod_id_array_size)
  {
    ModioFilterCreator filter;
    modioInitFilter(&filter);
    while (i < mod_id_array_size)
    {
      modioAddFilterInField(&filter, "id", modio::toString(mod_id_array[i]).c_str());
      i++;
      if(i%100 == 0)
        break;
    }
    modioGetAllMods(NULL, filter, &onModioCheckIfModsAreUpdate);
    modioFreeFilter(&filter);
  }
}
}
