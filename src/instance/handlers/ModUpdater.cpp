#include "instance/handlers/ModUpdater.h"

namespace modio
{
  ModUpdater::ModUpdater()
  {
    this->mod_updater = new ModioModUpdater;
    modioInitModUpdater(this->mod_updater);
  }

  void ModUpdater::setName(const std::string& name)
  {
    modioSetModUpdaterName(this->mod_updater, (char*)name.c_str());
  }

  void ModUpdater::setHomepage(const std::string& homepage)
  {
    modioSetModUpdaterHomepage(this->mod_updater, (char*)homepage.c_str());
  }

  void ModUpdater::setSummary(const std::string& summary)
  {
    modioSetModUpdaterSummary(this->mod_updater, (char*)summary.c_str());
  }

  void ModUpdater::setDescription(const std::string& description)
  {
    modioSetModUpdaterDescription(this->mod_updater, (char*)description.c_str());
  }

  void ModUpdater::setMetadataBlob(const std::string& metadata_blob)
  {
    modioSetModUpdaterMetadataBlob(this->mod_updater, (char*)metadata_blob.c_str());
  }

  void ModUpdater::setNameid(const std::string& name_id)
  {
    modioSetModUpdaterNameid(this->mod_updater, (char*)name_id.c_str());
  }

  void ModUpdater::setModfile(u32 modfile)
  {
    modioSetModUpdaterModfile(this->mod_updater, modfile);
  }

  ModioModUpdater* ModUpdater::getModioModUpdater()
  {
    return this->mod_updater;
  }

  ModUpdater::~ModUpdater()
  {
    modioFreeModUpdater(this->mod_updater);
  }
}
