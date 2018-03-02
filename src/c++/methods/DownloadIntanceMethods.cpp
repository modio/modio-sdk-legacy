#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::installMod(u32 mod_id, const std::function<void(const modio::Response& response)>& callback)
  {
    const struct InstallModCall* install_modfile_call = new InstallModCall{callback};
    install_mod_calls[this->current_call_id] = (InstallModCall*)install_modfile_call;

    modioInstallMod((void*)new u32(this->current_call_id), mod_id, &onInstallModfile);

    this->current_call_id++;
  }

  u32 Instance::getModfileState(u32 modfile_id)
  {
    return modioGetModfileState(modfile_id);
  }

  double Instance::getModfileDownloadPercentage(u32 modfile_id)
  {
    return modioGetModfileDownloadPercentage(modfile_id);
  }

  bool Instance::uninstallModfile(u32 modfile_id)
  {
    return modioUninstallModfile(modfile_id);
  }

  std::vector<u32> Instance::getInstalledModfileIds()
  {
    std::vector<u32> installed_modfile_ids;
    u32 installed_modfiles_count = modioGetInstalledModfilesCount();
    for(u32 i=0; i<installed_modfiles_count; i++)
    {
      installed_modfile_ids.push_back(modioGetInstalledModfileId(i));
    }
    return installed_modfile_ids;
  }

  void Instance::pauseCurrentDownload()
  {
    modioPauseCurrentDownload();
  }

  void Instance::resumeCurrentDownload()
  {
    modioResumeCurrentDownload();
  }

  std::vector<modio::InstalledMod> Instance::getInstalledMods()
  {
	  std::vector<modio::InstalledMod> installed_mods;

	  u32 installed_mods_size = modioGetInstalledModsSize();
	  ModioInstalledMod* modio_installed_mods = new ModioInstalledMod[installed_mods_size];

	  installed_mods.resize(installed_mods_size);
	  for (u32 i = 0; i<(u32)installed_mods_size; i++)
	  {
		modio::InstalledMod installed_mod;
		installed_mods[i].initialize(modio_installed_mods[i]);
	  }

	  delete[] modio_installed_mods;

	  return installed_mods;
  }
}
