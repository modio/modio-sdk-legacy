#include "instance/handlers/ModfileUpdater.h"

namespace modio
{
  ModfileUpdater::ModfileUpdater()
  {
    this->modfile_updater = new ModioModfileUpdater;
    modioInitModfileUpdater(this->modfile_updater);
  }

  void ModfileUpdater::setVersion(const std::string& version)
  {
    modioSetModfileUpdaterVersion(this->modfile_updater, (char*)version.c_str());
  }

  void ModfileUpdater::setChangelog(const std::string& changelog)
  {
    modioSetModfileUpdaterChangelog(this->modfile_updater, (char*)changelog.c_str());
  }

  void ModfileUpdater::setActive(bool active)
  {
    modioSetModfileUpdaterActive(this->modfile_updater, active);
  }

  ModioModfileUpdater* ModfileUpdater::getModioModfileUpdater()
  {
    return this->modfile_updater;
  }

  ModfileUpdater::~ModfileUpdater()
  {
    modioFreeModfileUpdater(this->modfile_updater);
  }
}
