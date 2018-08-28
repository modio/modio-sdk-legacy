#include "c/creators/ModioModfileCreator.h"

extern "C"
{
  void modioInitModfileCreator(ModioModfileCreator* modfile_creator)
  {
    modfile_creator->path = NULL;
    modfile_creator->version = NULL;
    modfile_creator->changelog = NULL;
    modfile_creator->metadata_blob = NULL;
    modfile_creator->active = NULL;
    modfile_creator->filehash = NULL;
  }

  void modioSetModfileCreatorPath(ModioModfileCreator* modfile_creator, char* path)
  {
    if(modfile_creator->path)
    delete[] modfile_creator->path;

    modfile_creator->path = new char[strlen(path) + 1];
    strcpy(modfile_creator->path, path);
  }

  void modioSetModfileCreatorVersion(ModioModfileCreator* modfile_creator, char* version)
  {
    if(modfile_creator->version)
      delete[] modfile_creator->version;

    modfile_creator->version = new char[strlen(version) + 1];
    strcpy(modfile_creator->version, version);
  }

  void modioSetModfileCreatorChangelog(ModioModfileCreator* modfile_creator, char* changelog)
  {
    if(modfile_creator->changelog)
      delete[] modfile_creator->changelog;

    modfile_creator->changelog = new char[strlen(changelog) + 1];
    strcpy(modfile_creator->changelog, changelog);
  }

  void modioSetModfileCreatorMetadataBlob(ModioModfileCreator* modfile_creator, char* metadata_blob)
  {
    if(modfile_creator->metadata_blob)
      delete[] modfile_creator->metadata_blob;

    modfile_creator->metadata_blob = new char[strlen(metadata_blob) + 1];
    strcpy(modfile_creator->metadata_blob, metadata_blob);
  }

  void modioSetModfileCreatorActive(ModioModfileCreator* modfile_creator, bool active)
  {
    if(modfile_creator->active)
      delete[] modfile_creator->active;

    modfile_creator->active = new char[2];

    if(active)
      strcpy(modfile_creator->active, "1");
    else
      strcpy(modfile_creator->active, "0");
  }

  void modioSetModfileCreatorFilehash(ModioModfileCreator* modfile_creator, char* filehash)
  {
    if(modfile_creator->filehash)
      delete[] modfile_creator->filehash;

    modfile_creator->filehash = new char[strlen(filehash) + 1];
    strcpy(modfile_creator->filehash, filehash);
  }

  void modioFreeModfileCreator(ModioModfileCreator* modfile_creator)
  {
    if(modfile_creator->path)
      delete[] modfile_creator->path;

    if(modfile_creator->version)
      delete[] modfile_creator->version;

    if(modfile_creator->changelog)
      delete[] modfile_creator->changelog;

    if(modfile_creator->metadata_blob)
      delete[] modfile_creator->metadata_blob;

    if(modfile_creator->active)
      delete[] modfile_creator->active;

    if(modfile_creator->filehash)
      delete[] modfile_creator->filehash;
  }
}

namespace modio
{
  std::multimap<std::string, std::string> convertModfileCreatorToMultimap(ModioModfileCreator* modfile_creator)
  {
    std::multimap<std::string, std::string> result;

    if(modfile_creator->path)
      result.insert(std::pair<std::string,std::string>("path",modfile_creator->path));

    if(modfile_creator->version)
      result.insert(std::pair<std::string,std::string>("version",modfile_creator->version));

    if(modfile_creator->changelog)
      result.insert(std::pair<std::string,std::string>("changelog",modfile_creator->changelog));

    if(modfile_creator->metadata_blob)
      result.insert(std::pair<std::string,std::string>("metadata_blob",modfile_creator->metadata_blob));

    if(modfile_creator->active)
      result.insert(std::pair<std::string,std::string>("active",modfile_creator->active));

    if(modfile_creator->filehash)
      result.insert(std::pair<std::string,std::string>("filehash",modfile_creator->filehash));

    return result;
  }

  void modioInitModfileCreatorFromJson(ModioModfileCreator* modfile_creator, nlohmann::json modfile_creator_json)
  {
    modfile_creator->path = NULL;
    if(modio::hasKey(modfile_creator_json, "path"))
    {
      std::string path_str = modfile_creator_json["path"];
      modfile_creator->path = new char[path_str.size() + 1];
      strcpy(modfile_creator->path, path_str.c_str());
    }

    modfile_creator->version = NULL;
    if(modio::hasKey(modfile_creator_json, "version"))
    {
      std::string version_str = modfile_creator_json["version"];
      modfile_creator->version = new char[version_str.size() + 1];
      strcpy(modfile_creator->version, version_str.c_str());
    }

    modfile_creator->changelog = NULL;
    if(modio::hasKey(modfile_creator_json, "changelog"))
    {
      std::string changelog_str = modfile_creator_json["changelog"];
      modfile_creator->changelog = new char[changelog_str.size() + 1];
      strcpy(modfile_creator->changelog, changelog_str.c_str());
    }

    modfile_creator->metadata_blob = NULL;
    if(modio::hasKey(modfile_creator_json, "metadata_blob"))
    {
      std::string metadata_blob_str = modfile_creator_json["metadata_blob"];
      modfile_creator->metadata_blob = new char[metadata_blob_str.size() + 1];
      strcpy(modfile_creator->metadata_blob, metadata_blob_str.c_str());
    }

    modfile_creator->active = NULL;
    if(modio::hasKey(modfile_creator_json, "active"))
    {
      std::string active_str = modfile_creator_json["active"];
      modfile_creator->active = new char[active_str.size() + 1];
      strcpy(modfile_creator->active, active_str.c_str());
    }

    modfile_creator->filehash = NULL;
    if(modio::hasKey(modfile_creator_json, "filehash"))
    {
      std::string filehash_str = modfile_creator_json["filehash"];
      modfile_creator->filehash = new char[filehash_str.size() + 1];
      strcpy(modfile_creator->filehash, filehash_str.c_str());
    }
  }
}
