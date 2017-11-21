#include "handlers/ModfileHandler.h"

extern "C"
{
  void modioInitModfileHandler(ModioModfileHandler* modfile_handler)
  {
    modfile_handler->path = NULL;
    modfile_handler->version = NULL;
    modfile_handler->changelog = NULL;
    modfile_handler->active = NULL;
  }

  void modioSetModfileVersion(ModioModfileHandler* modfile_handler, char* version)
  {
    if(modfile_handler->version)
      delete[] modfile_handler->version;

    modfile_handler->version = new char[strlen(version) + 1];
    strcpy(modfile_handler->version, version);
  }

  void modioSetModfileChangelog(ModioModfileHandler* modfile_handler, char* changelog)
  {
    if(modfile_handler->changelog)
      delete[] modfile_handler->changelog;

    modfile_handler->changelog = new char[strlen(changelog) + 1];
    strcpy(modfile_handler->changelog, changelog);
  }

  void modioSetModfilePath(ModioModfileHandler* modfile_handler, char* path)
  {
    if(modfile_handler->path)
      delete[] modfile_handler->path;

    modfile_handler->path = new char[strlen(path) + 1];
    strcpy(modfile_handler->path, path);
  }

  void modioSetModfileActive(ModioModfileHandler* modfile_handler, bool active)
  {
    if(modfile_handler->active)
      delete[] modfile_handler->active;

    modfile_handler->active = new char[2];

    if(active)
      strcpy(modfile_handler->active, "1");
    else
      strcpy(modfile_handler->active, "0");
  }

  void modioDeleteModfileHandler(ModioModfileHandler* modfile_handler)
  {
    if(modfile_handler->path)
      delete modfile_handler->path;

    if(modfile_handler->path)
      delete modfile_handler->path;

    if(modfile_handler->version)
      delete modfile_handler->version;

    if(modfile_handler->changelog)
      delete modfile_handler->changelog;

    if(modfile_handler->active)
      delete modfile_handler->active;
  }
}

namespace modio
{
  std::multimap<std::string, std::string> modfileHandlerToMultimap(ModioModfileHandler* modfile_handler)
  {
    std::multimap<std::string, std::string> result;

    if(modfile_handler->path)
      result.insert(std::pair<std::string,std::string>("path",modfile_handler->path));

    if(modfile_handler->version)
      result.insert(std::pair<std::string,std::string>("version",modfile_handler->version));

    if(modfile_handler->changelog)
      result.insert(std::pair<std::string,std::string>("changelog",modfile_handler->changelog));

    if(modfile_handler->active)
      result.insert(std::pair<std::string,std::string>("active",modfile_handler->active));

    return result;
  }
}
