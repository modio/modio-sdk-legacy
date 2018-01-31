#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::addModfile(u32 mod_id, modio::ModfileCreator& modfile_handler, const std::function<void(const modio::Response& response, const modio::Modfile& modfile)>& callback)
  {
    const struct AddModfileCall* add_modfile_call = new AddModfileCall{callback};
    add_modfile_calls[this->current_call_id] = (AddModfileCall*)add_modfile_call;

    modioAddModfile((void*)new u32(this->current_call_id), mod_id, *modfile_handler.getModioModfileCreator(), &onAddModfile);

    this->current_call_id++;
  }

  void Instance::editModfile(u32 mod_id, u32 modfile_id, modio::ModfileEditor& modfile_handler, const std::function<void(const modio::Response& response, const modio::Modfile& modfile)>& callback)
  {
    const struct EditModfileCall* edit_modfile_call = new EditModfileCall{callback};
    edit_modfile_calls[this->current_call_id] = (EditModfileCall*)edit_modfile_call;

    modioEditModfile((void*)new u32(this->current_call_id), mod_id, modfile_id, *modfile_handler.getModioModfileEditor(), &onEditModfile);

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
