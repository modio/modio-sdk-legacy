#ifndef MODIO_MODFILE_HANDLER_H
#define MODIO_MODFILE_HANDLER_H

#include "Globals.h"

#ifdef WINDOWS
#  ifdef BUILDING_MODIO_DLL
#    define MODIO_DLL __declspec(dllexport)
#  else
#    define MODIO_DLL __declspec(dllimport)
#  endif
#else
#  define MODIO_DLL
#endif

namespace modio
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
