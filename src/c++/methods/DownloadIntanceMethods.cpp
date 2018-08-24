#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::installMod(u32 mod_id)
  {
    modioInstallMod(mod_id);
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

  std::list<QueuedModDownload *> Instance::getModDownloadQueue()
  {
    return curlwrapper::getModDownloadQueue();
  }

  std::list<QueuedModfileUpload *> Instance::getModfileUploadQueue()
  {
    return curlwrapper::getModfileUploadQueue();
  }

  std::vector<modio::InstalledMod> Instance::getAllInstalledMods()
  {
	  std::vector<modio::InstalledMod> installed_mods;

	  u32 installed_mods_size = modioGetAllInstalledModsCount();
	  ModioInstalledMod* modio_installed_mods = new ModioInstalledMod[installed_mods_size];
    modioGetAllInstalledMods(modio_installed_mods);
    
	  installed_mods.resize(installed_mods_size);
	  for (u32 i = 0; i<(u32)installed_mods_size; i++)
	  {
		modio::InstalledMod installed_mod;
		installed_mods[i].initialize(modio_installed_mods[i]);
	  }

	  delete[] modio_installed_mods;

	  return installed_mods;
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
}
