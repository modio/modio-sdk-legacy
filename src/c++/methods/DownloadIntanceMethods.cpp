#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::installModfile(u32 mod_id, const std::string& destination_path, const std::function<void(const modio::Response& response)>& callback)
  {
    const struct InstallModCall* install_modfile_call = new InstallModCall{callback};
    install_mod_calls[this->current_call_id] = (InstallModCall*)install_modfile_call;

    modioInstallMod((void*)new u32(this->current_call_id), mod_id, (char*)destination_path.c_str(), &onInstallModfile);

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
}
