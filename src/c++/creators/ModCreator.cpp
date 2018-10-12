#include "c++/creators/ModCreator.h"

namespace modio
{
  ModCreator::ModCreator()
  {
    this->mod_creator = new ModioModCreator;
    modioInitModCreator(this->mod_creator);
  }

  void ModCreator::setVisible(u32 visible)
  {
    modioSetModCreatorVisible(this->mod_creator, visible);
  }

  void ModCreator::setMaturityOption(u32 maturity_option)
  {
    modioSetModCreatorMaturityOption(this->mod_creator, maturity_option);
  }

  void ModCreator::setLogoPath(const std::string& path)
  {
    modioSetModCreatorLogoPath(this->mod_creator, (char*)path.c_str());
  }

  void ModCreator::setName(const std::string& name)
  {
    modioSetModCreatorName(this->mod_creator, (char*)name.c_str());
  }

  void ModCreator::setHomepageURL(const std::string& homepage_url)
  {
    modioSetModCreatorHomepageURL(this->mod_creator, (char*)homepage_url.c_str());
  }

  void ModCreator::setSummary(const std::string& summary)
  {
    modioSetModCreatorSummary(this->mod_creator, (char*)summary.c_str());
  }

  void ModCreator::setDescription(const std::string& description)
  {
    modioSetModCreatorDescription(this->mod_creator, (char*)description.c_str());
  }

  void ModCreator::setMetadataBlob(const std::string& metadata_blob)
  {
    modioSetModCreatorMetadataBlob(this->mod_creator, (char*)metadata_blob.c_str());
  }

  void ModCreator::setNameid(const std::string& name_id)
  {
    modioSetModCreatorNameid(this->mod_creator, (char*)name_id.c_str());
  }

  void ModCreator::addTag(const std::string& tag)
  {
    modioAddModCreatorTag(this->mod_creator, (char*)tag.c_str());
  }

  ModioModCreator* ModCreator::getModioModCreator()
  {
    return this->mod_creator;
  }

  ModCreator::~ModCreator()
  {
    modioFreeModCreator(this->mod_creator);
    delete this->mod_creator;
  }
}
