#include "handlers/ModfileHandler.h"

namespace modio
{
  void setVersion(ModfileHandler* modfile_handler, string version)
  {
    modfile_handler->curlform_copycontents.insert(pair<string,string>("version",version));
  }

  void setChangelog(ModfileHandler* modfile_handler, string changelog)
  {
    modfile_handler->curlform_copycontents.insert(pair<string,string>("changelog",changelog));
  }

  void setPath(ModfileHandler* modfile_handler, string path)
  {
    modfile_handler->path = path;
  }

  void setActive(ModfileHandler* modfile_handler, string active)
  {
    modfile_handler->curlform_copycontents.insert(pair<string,string>("active",active));
  }
}
