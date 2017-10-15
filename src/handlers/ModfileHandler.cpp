#include "handlers/ModfileHandler.h"

namespace modio
{
  void ModfileHandler::setVersion(string version)
  {
    this->curlform_copycontents.insert(pair<string,string>("version",version));
  }

  void ModfileHandler::setChangelog(string changelog)
  {
    this->curlform_copycontents.insert(pair<string,string>("changelog",changelog));
  }

  void ModfileHandler::setPath(string path)
  {
    this->path = path;
  }

  void ModfileHandler::setActive(string active)
  {
    this->curlform_copycontents.insert(pair<string,string>("active",active));
  }
}
