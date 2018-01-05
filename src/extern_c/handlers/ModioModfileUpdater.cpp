#include "extern_c/handlers/ModioModfileUpdater.h"

extern "C"
{
  void modioInitUpdateModfileHandler(ModioModfileUpdater* modfile_creator)
  {
    modfile_creator->version = NULL;
    modfile_creator->changelog = NULL;
    modfile_creator->active = NULL;
  }

  void modioSetUpdateModfileVersion(ModioModfileUpdater* modfile_creator, char* version)
  {
    if(modfile_creator->version)
      delete[] modfile_creator->version;

    modfile_creator->version = new char[strlen(version) + 1];
    strcpy(modfile_creator->version, version);
  }

  void modioSetUpdateModfileChangelog(ModioModfileUpdater* modfile_creator, char* changelog)
  {
    if(modfile_creator->changelog)
      delete[] modfile_creator->changelog;

    modfile_creator->changelog = new char[strlen(changelog) + 1];
    strcpy(modfile_creator->changelog, changelog);
  }

  void modioSetUpdateModfileActive(ModioModfileUpdater* modfile_creator, bool active)
  {
    if(modfile_creator->active)
      delete[] modfile_creator->active;

    modfile_creator->active = new char[2];

    if(active)
      strcpy(modfile_creator->active, "1");
    else
      strcpy(modfile_creator->active, "0");
  }

  void modioDeleteUpdateModfileHandler(ModioModfileUpdater* modfile_creator)
  {
    if(modfile_creator->version)
      delete modfile_creator->version;

    if(modfile_creator->changelog)
      delete modfile_creator->changelog;

    if(modfile_creator->active)
      delete modfile_creator->active;
  }
}

namespace modio
{
  std::multimap<std::string, std::string> convertModfileUpdaterToMultimap(ModioModfileUpdater* modfile_creator)
  {
    std::multimap<std::string, std::string> result;

    if(modfile_creator->version)
      result.insert(std::pair<std::string,std::string>("version",modfile_creator->version));

    if(modfile_creator->changelog)
      result.insert(std::pair<std::string,std::string>("changelog",modfile_creator->changelog));

    if(modfile_creator->active)
      result.insert(std::pair<std::string,std::string>("active",modfile_creator->active));

    return result;
  }
}
