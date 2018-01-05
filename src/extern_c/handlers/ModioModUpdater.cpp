#include "extern_c/handlers/ModioModUpdater.h"

extern "C"
{
  void modioInitUpdateModHandler(ModioModUpdater* mod_updater)
  {
    mod_updater->name = NULL;
    mod_updater->name_id = NULL;
    mod_updater->summary = NULL;
    mod_updater->description = NULL;
    mod_updater->homepage = NULL;
    mod_updater->metadata_blob = NULL;
    mod_updater->status = NULL;
  }

  void modioSetUpdateModName(ModioModUpdater* mod_updater, char* name)
  {
    if(mod_updater->name)
      delete[] mod_updater->name;

    mod_updater->name = new char[strlen(name) + 1];
    strcpy(mod_updater->name, name);
  }

  void modioSetUpdateModNameid(ModioModUpdater* mod_updater, char* name_id)
  {
    if(mod_updater->name_id)
    delete[] mod_updater->name_id;

    mod_updater->name_id = new char[strlen(name_id) + 1];
    strcpy(mod_updater->name_id, name_id);
  }

  void modioSetUpdateModSummary(ModioModUpdater* mod_updater, char* summary)
  {
    if(mod_updater->summary)
    delete[] mod_updater->summary;

    mod_updater->summary = new char[strlen(summary) + 1];
    strcpy(mod_updater->summary, summary);
  }

  void modioSetUpdateModDescription(ModioModUpdater* mod_updater, char* description)
  {
    if(mod_updater->description)
    delete[] mod_updater->description;

    mod_updater->description = new char[strlen(description) + 1];
    strcpy(mod_updater->description, description);
  }

  void modioSetUpdateModHomepage(ModioModUpdater* mod_updater, char* homepage)
  {
    if(mod_updater->homepage)
      delete[] mod_updater->homepage;

    mod_updater->homepage = new char[strlen(homepage) + 1];
    strcpy(mod_updater->homepage, homepage);
  }

  void modioSetUpdateModModfile(ModioModUpdater* mod_updater, u32 modfile)
  {
    if(mod_updater->modfile)
    delete[] mod_updater->modfile;

    mod_updater->modfile = new char[modio::toString(modfile).size() + 1];
    strcpy(mod_updater->modfile, modio::toString(modfile).c_str());
  }

  void modioSetUpdateModMetadataBlob(ModioModUpdater* mod_updater, char* metadata_blob)
  {
    if(mod_updater->metadata_blob)
      delete[] mod_updater->metadata_blob;

    mod_updater->metadata_blob = new char[strlen(metadata_blob) + 1];
    strcpy(mod_updater->metadata_blob, metadata_blob);
  }

  void modioSetUpdateModStatus(ModioModUpdater* mod_updater, char* status)
  {
    if(mod_updater->status)
      delete[] mod_updater->status;

    mod_updater->status = new char[strlen(status) + 1];
    strcpy(mod_updater->status, status);
  }

  void modioFreeUpdateModHandler(ModioModUpdater* mod_updater)
  {
    delete mod_updater->name;
    delete mod_updater->name_id;
    delete mod_updater->summary;
    delete mod_updater->description;
    delete mod_updater->homepage;
    delete mod_updater->modfile;
    delete mod_updater->metadata_blob;
  }
}

namespace modio
{
  std::multimap<std::string, std::string> getModfileCurlFormCopyContentsParams(ModioModUpdater* mod_updater)
  {
    std::multimap<std::string, std::string> result;

    if(mod_updater->name)
      result.insert(std::pair<std::string,std::string>("name",mod_updater->name));

    if(mod_updater->name_id)
      result.insert(std::pair<std::string,std::string>("name_id",mod_updater->name_id));

    if(mod_updater->summary)
      result.insert(std::pair<std::string,std::string>("summary",mod_updater->summary));

    if(mod_updater->description)
      result.insert(std::pair<std::string,std::string>("description",mod_updater->description));

    if(mod_updater->homepage)
      result.insert(std::pair<std::string,std::string>("homepage",mod_updater->homepage));

    if(mod_updater->modfile)
      result.insert(std::pair<std::string,std::string>("modfile",mod_updater->modfile));

    if(mod_updater->metadata_blob)
      result.insert(std::pair<std::string,std::string>("metadata_blob",mod_updater->metadata_blob));

    if(mod_updater->status)
      result.insert(std::pair<std::string,std::string>("status",mod_updater->status));

    return result;
  }
}
