#include "instance/handlers/ModHandler.h"

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

  void ModHandler::setDescription(const std::string& description)
  {
    modioSetDescription(this->mod_handler, (char*)description.c_str());
  }

  void ModHandler::setMetadataBlob(const std::string& metadata_blob)
  {
    modioSetMetadataBlob(this->mod_handler, (char*)metadata_blob.c_str());
  }

  void ModHandler::setNameid(const std::string& name_id)
  {
    modioSetNameid(this->mod_handler, (char*)name_id.c_str());
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
