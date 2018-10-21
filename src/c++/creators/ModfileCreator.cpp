#include "c++/creators/ModfileCreator.h"

namespace modio
{
ModfileCreator::ModfileCreator()
{
  modioInitModfileCreator(&modio_modfile_creator);
}

void ModfileCreator::initializeFromModioModfileCreator(ModioModfileCreator& modio_modfile_creator)
{
  if (modio_modfile_creator.path)
  {
    this->modio_modfile_creator.path = new char[strlen(modio_modfile_creator.path) + 1];
    strcpy(this->modio_modfile_creator.path, modio_modfile_creator.path);
  }

  if (modio_modfile_creator.version)
  {
    this->modio_modfile_creator.version = new char[strlen(modio_modfile_creator.version) + 1];
    strcpy(this->modio_modfile_creator.version, modio_modfile_creator.version);
  }

  if (modio_modfile_creator.changelog)
  {
    this->modio_modfile_creator.changelog = new char[strlen(modio_modfile_creator.changelog) + 1];
    strcpy(this->modio_modfile_creator.changelog, modio_modfile_creator.changelog);
  }

  if (modio_modfile_creator.metadata_blob)
  {
    this->modio_modfile_creator.metadata_blob = new char[strlen(modio_modfile_creator.metadata_blob) + 1];
    strcpy(this->modio_modfile_creator.metadata_blob, modio_modfile_creator.metadata_blob);
  }

  if (modio_modfile_creator.active)
  {
    this->modio_modfile_creator.active = new char[strlen(modio_modfile_creator.active) + 1];
    strcpy(this->modio_modfile_creator.active, modio_modfile_creator.active);
  }

  if (modio_modfile_creator.filehash)
  {
    this->modio_modfile_creator.filehash = new char[strlen(modio_modfile_creator.filehash) + 1];
    strcpy(this->modio_modfile_creator.filehash, modio_modfile_creator.filehash);
  }
}

void ModfileCreator::setPath(const std::string &path)
{
  modioSetModfileCreatorPath(&modio_modfile_creator, (char *)path.c_str());
}

void ModfileCreator::setVersion(const std::string &version)
{
  modioSetModfileCreatorVersion(&modio_modfile_creator, (char *)version.c_str());
}

void ModfileCreator::setChangelog(const std::string &changelog)
{
  modioSetModfileCreatorChangelog(&modio_modfile_creator, (char *)changelog.c_str());
}

void ModfileCreator::setMetadataBlob(const std::string &metadata_blob)
{
  modioSetModfileCreatorMetadataBlob(&modio_modfile_creator, (char *)metadata_blob.c_str());
}

void ModfileCreator::setActive(bool active)
{
  modioSetModfileCreatorActive(&modio_modfile_creator, active);
}

ModioModfileCreator *ModfileCreator::getModioModfileCreator()
{
  return &modio_modfile_creator;
}

ModfileCreator::~ModfileCreator()
{
  modioFreeModfileCreator(&modio_modfile_creator);
}

nlohmann::json toJson(ModfileCreator &modfile_creator)
{
  nlohmann::json modfile_creator_json;

  if (modfile_creator.modio_modfile_creator.path)
    modfile_creator_json["path"] = modfile_creator.modio_modfile_creator.path;
  if (modfile_creator.modio_modfile_creator.version)
    modfile_creator_json["version"] = modfile_creator.modio_modfile_creator.version;
  if (modfile_creator.modio_modfile_creator.changelog)
    modfile_creator_json["changelog"] = modfile_creator.modio_modfile_creator.changelog;
  if (modfile_creator.modio_modfile_creator.metadata_blob)
    modfile_creator_json["metadata_blob"] = modfile_creator.modio_modfile_creator.metadata_blob;
  if (modfile_creator.modio_modfile_creator.active)
    modfile_creator_json["active"] = modfile_creator.modio_modfile_creator.active;
  if (modfile_creator.modio_modfile_creator.filehash)
    modfile_creator_json["filehash"] = modfile_creator.modio_modfile_creator.filehash;

  return modfile_creator_json;
}
} // namespace modio
