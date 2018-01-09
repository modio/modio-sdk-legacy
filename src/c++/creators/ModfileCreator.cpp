#include "c++/creators/ModfileCreator.h"

namespace modio
{
  ModfileCreator::ModfileCreator()
  {
    this->modfile_creator = new ModioModfileCreator;
    modioInitModfileCreator(this->modfile_creator);
  }

  void ModfileCreator::setPath(const std::string& path)
  {
    modioSetModfileCreatorPath(this->modfile_creator, (char*)path.c_str());
  }

  void ModfileCreator::setVersion(const std::string& version)
  {
    modioSetModfileCreatorVersion(this->modfile_creator, (char*)version.c_str());
  }

  void ModfileCreator::setChangelog(const std::string& changelog)
  {
    modioSetModfileCreatorChangelog(this->modfile_creator, (char*)changelog.c_str());
  }

  void ModfileCreator::setActive(bool active)
  {
    modioSetModfileCreatorActive(this->modfile_creator, active);
  }

  ModioModfileCreator* ModfileCreator::getModioModfileCreator()
  {
    return this->modfile_creator;
  }

  ModfileCreator::~ModfileCreator()
  {
    modioFreeModfileCreator(this->modfile_creator);
  }
}
