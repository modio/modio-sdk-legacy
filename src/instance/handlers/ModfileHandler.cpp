#include "instance/handlers/ModfileHandler.h"

namespace modio
{
  ModfileHandler::ModfileHandler()
  {
    this->modfile_handler = new ModioModfileHandler;
    modioInitModfileHandler(this->modfile_handler);
  }

  void ModfileHandler::setModfilePath(const std::string& path)
  {
    modioSetModfilePath(this->modfile_handler, (char*)path.c_str());
  }

  void ModfileHandler::setModfileVersion(const std::string& version)
  {
    modioSetModfileVersion(this->modfile_handler, (char*)version.c_str());
  }

  void ModfileHandler::setModfileChangelog(const std::string& changelog)
  {
    modioSetModfileChangelog(this->modfile_handler, (char*)changelog.c_str());
  }

  void ModfileHandler::setModfileActive(bool active)
  {
    modioSetModfileActive(this->modfile_handler, active);
  }

  ModioModfileHandler* ModfileHandler::getModioModfileHandler()
  {
    return this->modfile_handler;
  }

  ModfileHandler::~ModfileHandler()
  {
    modioDeleteModfileHandler(this->modfile_handler);
  }
}
