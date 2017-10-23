#ifndef MODIO_MODFILE_HANDLER_H
#define MODIO_MODFILE_HANDLER_H

#include "Globals.h"

extern "C"
{
  struct ModioModfileHandler
  {
    multimap<string, string> curlform_copycontents;
    string path;
  };

  void MODIO_DLL modioSetModfilePath(ModioModfileHandler* modfile_handler, string path);
  void MODIO_DLL modioSetModfileVersion(ModioModfileHandler* modfile_handler, string version);
  void MODIO_DLL modioSetModfileChangelog(ModioModfileHandler* modfile_handler, string changelog);
  void MODIO_DLL modioSetModfileActive(ModioModfileHandler* modfile_handler, bool active);
}

#endif
