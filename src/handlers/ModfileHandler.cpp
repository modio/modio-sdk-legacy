#include "handlers/ModfileHandler.h"

extern "C"
{
  void setModfileVersion(ModfileHandler* modfile_handler, string version)
  {
    modfile_handler->curlform_copycontents.insert(pair<string,string>("version",version));
  }

  void setModfileChangelog(ModfileHandler* modfile_handler, string changelog)
  {
    modfile_handler->curlform_copycontents.insert(pair<string,string>("changelog",changelog));
  }

  void setModfilePath(ModfileHandler* modfile_handler, string path)
  {
    modfile_handler->path = path;
  }

  void setModfileActive(ModfileHandler* modfile_handler, bool active)
  {
    string active_str = "0";
    if(active)
      active_str = "1";

    modfile_handler->curlform_copycontents.insert(pair<string,string>("active",active_str));
  }
}
