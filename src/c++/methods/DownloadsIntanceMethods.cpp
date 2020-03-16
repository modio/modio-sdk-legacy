#include "c++/ModIOInstance.h"
#include "Globals.h"
#include "ModioUtility.h"
#include "ModUtility.h"
#include "c++/methods/callbacks/DownloadsInstanceCallbacks.h"
#include "wrappers/CurlUtility.h"

namespace modio
{
void Instance::downloadMod(u32 mod_id)
{
  modioDownloadMod(mod_id);
}

void Instance::installDownloadedMods()
{
  modioInstallDownloadedMods();
}

void Instance::uninstallMod(u32 mod_id)
{
  modioUninstallMod(mod_id);
}

void Instance::pauseDownloads()
{
  modioPauseDownloads();
}

void Instance::resumeDownloads()
{
  modioResumeDownloads();
}

void Instance::prioritizeModDownload(u32 mod_id)
{
  modioPrioritizeModDownload(mod_id);
}

const std::list<QueuedModDownload *> Instance::getModDownloadQueue()
{
  return curlwrapper::getModDownloadQueue();
}

const std::list<QueuedModfileUpload *> Instance::getModfileUploadQueue()
{
  return curlwrapper::getModfileUploadQueue();
}

const modio::InstalledMod Instance::getInstalledMod(u32 mod_id)
{
  modio::InstalledMod installed_mod;
  ModioInstalledMod *modio_installed_mod = new ModioInstalledMod;

  modioGetInstalledMod(mod_id, modio_installed_mod);
  installed_mod.initialize(*modio_installed_mod);
  modioFreeInstalledMod(modio_installed_mod);

  delete modio_installed_mod;

  return installed_mod;
}

const std::vector<modio::InstalledMod> Instance::getAllInstalledMods()
{
  std::vector<modio::InstalledMod> all_installed_mods;

  u32 installed_mods_size = modioGetAllInstalledModsCount();
  ModioInstalledMod *modio_installed_mods = new ModioInstalledMod[installed_mods_size];
  modioGetAllInstalledMods(modio_installed_mods);

  all_installed_mods.resize(installed_mods_size);
  for (size_t i = 0; i < installed_mods_size; i++)
  {
    all_installed_mods[i].initialize(modio_installed_mods[i]);
    modioFreeInstalledMod(&modio_installed_mods[i]);
  }

  delete[] modio_installed_mods;

  return all_installed_mods;
}

const std::vector<u32> Instance::getAllDownloadedMods()
{
  std::vector<u32> downloaded_mods;
  for (auto &downloaded_mod : modio::g_downloaded_mods)
  {
    if(modio::hasKey(downloaded_mod, "mod") &&
        modio::hasKey(downloaded_mod["mod"], "id"))
    {
      downloaded_mods.push_back(downloaded_mod["mod"]["id"]);
    }
  }
  return downloaded_mods;
}

void Instance::setDownloadListener(const std::function<void(u32 response_code, u32 mod_id)> &callback)
{
  set_download_listener_call = new SetDownloadListenerCall{callback};
  modioSetDownloadListener(&onDownloadListener);
}

void Instance::setUploadListener(const std::function<void(u32 response_code, u32 mod_id)> &callback)
{
  set_upload_listener_call = new SetUploadListenerCall{callback};
  modioSetUploadListener(&onUploadListener);
}

u32 Instance::getModState(u32 mod_id)
{
  return modioGetModState(mod_id);
}

void Instance::checkIfModsAreUpdated(const std::vector<u32> mod_ids, const std::function<void(const modio::Response &, const bool mods_are_updated)> &callback)
{
	u32 *mod_id_array = new u32[mod_ids.size()];
	for (size_t i = 0; i < mod_ids.size(); i++)
		mod_id_array[i] = mod_ids[i];

	struct GetBoolCall *check_if_mods_are_updated_call = new GetBoolCall{callback};
	check_if_mods_are_updated_calls[current_call_id] = check_if_mods_are_updated_call;

	modioCheckIfModsAreUpdated((void*)((uintptr_t)current_call_id), mod_id_array, (u32)mod_ids.size(), &onCheckIfModsAreUpdated);
	current_call_id++;

	delete[] mod_id_array;
}
} // namespace modio
