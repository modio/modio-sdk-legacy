#ifndef MODIO_MODFILE_HANDLER_H
#define MODIO_MODFILE_HANDLER_H

#include "Globals.h"

extern "C"
{
  struct ModfileHandler
  {
    multimap<string, string> curlform_copycontents;
    string path;
  };

  void MODIO_DLL setModfilePath(ModfileHandler* modfile_handler, string path);
  void MODIO_DLL setModfileVersion(ModfileHandler* modfile_handler, string version);
  void MODIO_DLL setModfileChangelog(ModfileHandler* modfile_handler, string changelog);
  void MODIO_DLL setModfileActive(ModfileHandler* modfile_handler, string active);
}

#endif
