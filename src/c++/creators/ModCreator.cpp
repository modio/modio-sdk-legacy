#include "c++/creators/ModCreator.h"

namespace modio
{
  ModCreator::ModCreator()
  {
    mod_creator = new ModioModCreator;
    modioInitModCreator(mod_creator);
  }

  void ModCreator::setVisible(u32 visible)
  {
    modioSetModCreatorVisible(mod_creator, visible);
  }

  void ModCreator::setMaturityOption(u32 maturity_option)
  {
    modioSetModCreatorMaturityOption(mod_creator, maturity_option);
  }

  void ModCreator::setLogoPath(const std::string& path)
  {
    modioSetModCreatorLogoPath(mod_creator, path.c_str());
  }

  void ModCreator::setName(const std::string& name)
  {
    modioSetModCreatorName(mod_creator, name.c_str());
  }

  void ModCreator::setHomepageURL(const std::string& homepage_url)
  {
    modioSetModCreatorHomepageURL(mod_creator, homepage_url.c_str());
  }

  void ModCreator::setSummary(const std::string& summary)
  {
    modioSetModCreatorSummary(mod_creator, summary.c_str());
  }

  void ModCreator::setDescription(const std::string& description)
  {
    modioSetModCreatorDescription(mod_creator, description.c_str());
  }

  void ModCreator::setMetadataBlob(const std::string& metadata_blob)
  {
    modioSetModCreatorMetadataBlob(mod_creator, metadata_blob.c_str());
  }

  void ModCreator::setNameid(const std::string& name_id)
  {
    modioSetModCreatorNameid(mod_creator, name_id.c_str());
  }

  void ModCreator::addTag(const std::string& tag)
  {
    modioAddModCreatorTag(mod_creator, tag.c_str());
  }

  ModioModCreator* ModCreator::getModioModCreator()
  {
    return mod_creator;
  }

  ModCreator::~ModCreator()
  {
    modioFreeModCreator(mod_creator);
    delete mod_creator;
  }
}
