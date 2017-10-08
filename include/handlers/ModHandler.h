#include "Globals.h"

namespace modworks
{
  class ModHandler
  {
  public:
    map<string, string> curlform_copycontents;
    map<string, string> curlform_files;
    void setLogoPath(string logo_path);
    void setName(string name);
    void setHomepage(string homepage);
    void setSummary(string summary);
    void setPrice(double price);
    void setStock(int stock);
    void setDescription(string description);
    void setMetadata(string metadata);
    void setNameid(string nameid);
    void setModfile(int modfile);
  };
}
