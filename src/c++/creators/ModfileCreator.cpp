#include "c++/creators/ModfileCreator.h"

namespace modio
{
ModfileCreator::ModfileCreator()
{
  modioInitModfileCreator(&modio_modfile_creator);
}

void ModfileCreator::initializeFromModioModfileCreator(ModioModfileCreator& other_modfile_creator)
{
  if (other_modfile_creator.path)
  {
    modio_modfile_creator.path = new char[strlen(other_modfile_creator.path) + 1];
    strcpy(modio_modfile_creator.path, other_modfile_creator.path);
  }

  if (other_modfile_creator.version)
  {
    modio_modfile_creator.version = new char[strlen(other_modfile_creator.version) + 1];
    strcpy(modio_modfile_creator.version, other_modfile_creator.version);
  }

  if (other_modfile_creator.changelog)
  {
    modio_modfile_creator.changelog = new char[strlen(other_modfile_creator.changelog) + 1];
    strcpy(modio_modfile_creator.changelog, other_modfile_creator.changelog);
  }

  if (other_modfile_creator.metadata_blob)
  {
    modio_modfile_creator.metadata_blob = new char[strlen(other_modfile_creator.metadata_blob) + 1];
    strcpy(modio_modfile_creator.metadata_blob, other_modfile_creator.metadata_blob);
  }

  if (other_modfile_creator.active)
  {
    modio_modfile_creator.active = new char[strlen(other_modfile_creator.active) + 1];
    strcpy(modio_modfile_creator.active, other_modfile_creator.active);
  }

  if (other_modfile_creator.filehash)
  {
    modio_modfile_creator.filehash = new char[strlen(other_modfile_creator.filehash) + 1];
    strcpy(modio_modfile_creator.filehash, other_modfile_creator.filehash);
  }
}

void ModfileCreator::setPath(const std::string &path)
{
  modioSetModfileCreatorPath(&modio_modfile_creator, path.c_str());
}

void ModfileCreator::setVersion(const std::string &version)
{
  modioSetModfileCreatorVersion(&modio_modfile_creator, version.c_str());
}

void ModfileCreator::setChangelog(const std::string &changelog)
{
  modioSetModfileCreatorChangelog(&modio_modfile_creator, changelog.c_str());
}

void ModfileCreator::setMetadataBlob(const std::string &metadata_blob)
{
  modioSetModfileCreatorMetadataBlob(&modio_modfile_creator, metadata_blob.c_str());
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
