#include "Globals.h"

namespace modworks
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
