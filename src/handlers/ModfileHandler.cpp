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

  void modioSetModfileVersion(ModioModfileHandler* modfile_handler, string version)
  {
    if(modfile_handler->version)
      delete[] modfile_handler->version;

    modfile_handler->version = new char[version.size() + 1];
    strcpy(modfile_handler->version, version.c_str());
  }

  void modioSetModfileChangelog(ModioModfileHandler* modfile_handler, string changelog)
  {
    if(modfile_handler->changelog)
      delete[] modfile_handler->changelog;

    modfile_handler->changelog = new char[changelog.size() + 1];
    strcpy(modfile_handler->changelog, changelog.c_str());
  }

  void modioSetModfilePath(ModioModfileHandler* modfile_handler, string path)
  {
    if(modfile_handler->path)
      delete[] modfile_handler->path;

    modfile_handler->path = new char[path.size() + 1];
    strcpy(modfile_handler->path, path.c_str());
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
  multimap<string, string> modfileHandlerToMultimap(ModioModfileHandler* modfile_handler)
  {
    multimap<string, string> result;

    if(modfile_handler->path)
      result.insert(pair<string,string>("path",modfile_handler->path));

    if(modfile_handler->version)
      result.insert(pair<string,string>("version",modfile_handler->version));

    if(modfile_handler->changelog)
      result.insert(pair<string,string>("changelog",modfile_handler->changelog));

    if(modfile_handler->active)
      result.insert(pair<string,string>("active",modfile_handler->active));

    return result;
  }
}
