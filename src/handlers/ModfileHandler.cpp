#include "handlers/ModfileHandler.h"

extern "C"
{
  void modioSetModfileVersion(ModioModfileHandler* modfile_handler, string version)
  {
    modfile_handler->curlform_copycontents.insert(pair<string,string>("version",version));
  }

  void modioSetModfileChangelog(ModioModfileHandler* modfile_handler, string changelog)
  {
    modfile_handler->curlform_copycontents.insert(pair<string,string>("changelog",changelog));
  }

  void modioSetModfilePath(ModioModfileHandler* modfile_handler, string path)
  {
    modfile_handler->path = path;
  }

  void modioSetModfileActive(ModioModfileHandler* modfile_handler, bool active)
  {
    string active_str = "0";
    if(active)
      active_str = "1";

    modfile_handler->curlform_copycontents.insert(pair<string,string>("active",active_str));
  }
}
