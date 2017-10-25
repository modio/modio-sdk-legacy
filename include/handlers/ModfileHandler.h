#ifndef MODIO_MODFILE_HANDLER_H
#define MODIO_MODFILE_HANDLER_H

#include "Globals.h"

extern "C"
{
  struct ModioModfileHandler
  {
    char* path;
    char* version;
    char* changelog;
    char* active;
  };

  void MODIO_DLL modioInitModfileHandler(ModioModfileHandler* modfile_handler);
  void MODIO_DLL modioSetModfilePath(ModioModfileHandler* modfile_handler, string path);
  void MODIO_DLL modioSetModfileVersion(ModioModfileHandler* modfile_handler, string version);
  void MODIO_DLL modioSetModfileChangelog(ModioModfileHandler* modfile_handler, string changelog);
  void MODIO_DLL modioSetModfileActive(ModioModfileHandler* modfile_handler, bool active);
  void MODIO_DLL modioDeleteModfileHandler(ModioModfileHandler* modfile_handler);
}

namespace modio
{
  multimap<string, string> modfileHandlerToMultimap(ModioModfileHandler* modfile_handler);
}

#endif
