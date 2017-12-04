#include "handlers_instance/ModHandler.h"

namespace modio
{
  ModHandler::ModHandler()
  {
    this->mod_handler = new ModioModHandler;
    modioInitModHandler(this->mod_handler);
  }

  void ModHandler::setLogoPath(const std::string& path)
  {
    modioSetLogoPath(this->mod_handler, (char*)path.c_str());
  }

  void ModHandler::setName(const std::string& name)
  {
    modioSetName(this->mod_handler, (char*)name.c_str());
  }

  void ModHandler::setHomepage(const std::string& homepage)
  {
    modioSetHomepage(this->mod_handler, (char*)homepage.c_str());
  }

  void ModHandler::setSummary(const std::string& summary)
  {
    modioSetSummary(this->mod_handler, (char*)summary.c_str());
  }

  void ModHandler::setPrice(double price)
  {
    modioSetPrice(this->mod_handler, price);
  }

  void ModHandler::setStock(int stock)
  {
    modioSetStock(this->mod_handler, stock);
  }

  void ModHandler::setDescription(const std::string& description)
  {
    modioSetDescription(this->mod_handler, (char*)description.c_str());
  }

  void ModHandler::setMetadata(const std::string& metadata)
  {
    modioSetMetadata(this->mod_handler, (char*)metadata.c_str());
  }

  void ModHandler::setNameid(const std::string& nameid)
  {
    modioSetNameid(this->mod_handler, (char*)nameid.c_str());
  }

  void ModHandler::setModfile(int modfile)
  {
    modioSetModfile(this->mod_handler, modfile);
  }

  void ModHandler::addTag(const std::string& tag)
  {
    modioAddTag(this->mod_handler, (char*)tag.c_str());
  }

  ModioModHandler* ModHandler::getModioModHandler()
  {
    return this->mod_handler;
  }

  ModHandler::~ModHandler()
  {
    modioFreeModHandler(this->mod_handler);
  }
}
