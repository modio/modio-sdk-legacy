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
    void setPath(string path);
    void setVersion(string version);
    void setChangelog(string changelog);
    void setActive(string active);
  };
}

#endif
