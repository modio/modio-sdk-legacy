#include "instance/ModIOInstance.h"

namespace modio
{
  struct AddModfileCall
  {
    const std::function<void(const modio::Response& response, const modio::Modfile& modfile)> callback;
  };

  struct EditModfileCall
  {
    const std::function<void(const modio::Response& response, const modio::Modfile& modfile)> callback;
  };

  struct InstallModfileCall
  {
    const std::function<void(const modio::Response& response)> callback;
  };

  std::map<int, AddModfileCall*> add_modfile_calls;
  std::map<int, EditModfileCall*> edit_modfile_calls;
  std::map<int, InstallModfileCall*> install_modfile_calls;

  void onAddModfile(void* object, ModioResponse modio_response, ModioModfile modio_modfile)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Modfile modfile;
    modfile.initialize(modio_modfile);

    add_modfile_calls[call_id]->callback(response, modfile);

    delete (int*)object;
    delete add_modfile_calls[call_id];
    add_modfile_calls.erase(call_id);
  }

  void onEditModfile(void* object, ModioResponse modio_response, ModioModfile modio_modfile)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);
    modio::Modfile modfile;

    modfile.initialize(modio_modfile);
    edit_modfile_calls[call_id]->callback(response, modfile);
    delete (int*)object;
    delete edit_modfile_calls[call_id];
    edit_modfile_calls.erase(call_id);
  }

  void onInstallModfile(void* object, ModioResponse modio_response)
  {
    int call_id = *((int*)object);
    modio::Response response;
    response.initialize(modio_response);
    install_modfile_calls[call_id]->callback(response);
    delete (int*)object;
    delete install_modfile_calls[call_id];
    install_modfile_calls.erase(call_id);
  }

  void Instance::addModfile(u32 mod_id, modio::ModfileHandler& modfile_handler, const std::function<void(const modio::Response& response, const modio::Modfile& modfile)>& callback)
  {
    const struct AddModfileCall* add_modfile_call = new AddModfileCall{callback};
    add_modfile_calls[this->current_call_id] = (AddModfileCall*)add_modfile_call;

    modioAddModfile((void*)new int(this->current_call_id), mod_id, *modfile_handler.getModioModfileHandler(), &onAddModfile);

    this->current_call_id++;
  }

  void Instance::editModfile(u32 mod_id, u32 modfile_id, modio::ModfileHandler& modfile_handler, const std::function<void(const modio::Response& response, const modio::Modfile& modfile)>& callback)
  {
    const struct EditModfileCall* edit_modfile_call = new EditModfileCall{callback};
    edit_modfile_calls[this->current_call_id] = (EditModfileCall*)edit_modfile_call;

    modioEditModfile((void*)new int(this->current_call_id), mod_id, modfile_id, *modfile_handler.getModioModfileHandler(), &onEditModfile);

    this->current_call_id++;
  }

  void Instance::installModfile(modio::Modfile modfile, const std::string& destination_path, const std::function<void(const modio::Response& response)>& callback)
  {
    const struct InstallModfileCall* install_modfile_call = new InstallModfileCall{callback};
    install_modfile_calls[this->current_call_id] = (InstallModfileCall*)install_modfile_call;

    modioInstallModfile((void*)new int(this->current_call_id), modfile.id, (char*)modfile.download_url.c_str(), (char*)destination_path.c_str(), &onInstallModfile);

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

  u32 Instance::getInstalledModfilesCount()
  {
    return modioGetInstalledModfilesCount();
  }

  std::vector<u32> Instance::getInstalledModfileIds()
  {
    std::vector<u32> installed_modfile_ids;
    u32 installed_modfiles_count = getInstalledModfilesCount();
    for(int i=0; i<installed_modfiles_count; i++)
    {
      installed_modfile_ids.push_back(modioGetInstalledModfileId(i));
    }
    return installed_modfile_ids;
  }
}
