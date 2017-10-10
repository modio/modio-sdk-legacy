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
  class ModfileHandler
  {
  public:
    map<string, string> curlform_copycontents;
    string path;
    void MODIO_DLL setPath(string path);
    void MODIO_DLL setVersion(string version);
    void MODIO_DLL setChangelog(string changelog);
    void MODIO_DLL setActive(string active);
  };
}

#endif
