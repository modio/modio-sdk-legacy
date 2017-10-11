#ifndef MODIO_MODFILE_HANDLER_H
#define MODIO_MODFILE_HANDLER_H

#include "Globals.h"

namespace modio
{
  class ModfileHandler
  {
  public:
    map<string, string> curlform_copycontents;
    string path;
    MODIO_DLL void setPath(string path);
    MODIO_DLL void setVersion(string version);
    MODIO_DLL void setChangelog(string changelog);
    MODIO_DLL void setActive(string active);
  };
}

#endif
