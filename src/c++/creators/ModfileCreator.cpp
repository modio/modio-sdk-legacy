#include "c++/creators/ModfileCreator.h"

namespace modio
{
  ModfileCreator::ModfileCreator()
  {
    this->modfile_creator = new ModioModfileCreator;
    modioInitModfileCreator(this->modfile_creator);
  }

  void ModfileCreator::initializeFromModioModfileCreator(ModioModfileCreator* modfile_creator)
  {
    this->modfile_creator = new ModioModfileCreator;
    modioInitModfileCreator(this->modfile_creator);

    if(modfile_creator)
    {
      if(modfile_creator->path)
      {
        this->modfile_creator->path = new char[strlen(modfile_creator->path) + 1];
        strcpy(this->modfile_creator->path, modfile_creator->path);
      }

      if(modfile_creator->version)
      {
        this->modfile_creator->version = new char[strlen(modfile_creator->version) + 1];
        strcpy(this->modfile_creator->version, modfile_creator->version);
      }

      if(modfile_creator->changelog)
      {
        this->modfile_creator->changelog = new char[strlen(modfile_creator->changelog) + 1];
        strcpy(this->modfile_creator->changelog, modfile_creator->changelog);
      }

      if(modfile_creator->metadata_blob)
      {
        this->modfile_creator->metadata_blob = new char[strlen(modfile_creator->metadata_blob) + 1];
        strcpy(this->modfile_creator->metadata_blob, modfile_creator->metadata_blob);
      }

      if(modfile_creator->active)
      {
        this->modfile_creator->active = new char[strlen(modfile_creator->active) + 1];
        strcpy(this->modfile_creator->active, modfile_creator->active);
      }

      if(modfile_creator->filehash)
      {
        this->modfile_creator->filehash = new char[strlen(modfile_creator->filehash) + 1];
        strcpy(this->modfile_creator->filehash, modfile_creator->filehash);
      }
    }
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

  void ModfileCreator::setMetadataBlob(const std::string& metadata_blob)
  {
    modioSetModfileCreatorMetadataBlob(this->modfile_creator, (char*)metadata_blob.c_str());
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

  nlohmann::json ModfileCreator::toJson()
  {
    nlohmann::json modfile_creator_json;

    if(this->modfile_creator->path)
      modfile_creator_json["path"] = this->modfile_creator->path;
    if(this->modfile_creator->version)
      modfile_creator_json["version"] = this->modfile_creator->version;
    if(this->modfile_creator->changelog)
      modfile_creator_json["changelog"] = this->modfile_creator->changelog;
    if(this->modfile_creator->metadata_blob)
      modfile_creator_json["metadata_blob"] = this->modfile_creator->metadata_blob;
    if(this->modfile_creator->active)
      modfile_creator_json["active"] = this->modfile_creator->active;
    if(this->modfile_creator->filehash)
      modfile_creator_json["filehash"] = this->modfile_creator->filehash;

    return modfile_creator_json;
  }  
}
