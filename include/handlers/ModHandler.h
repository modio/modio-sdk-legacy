#ifndef MODIO_MOD_HANDLER_H
#define MODIO_MOD_HANDLER_H

#include "Globals.h"

namespace modio
{
  class ModHandler
  {
  public:
    map<string, string> curlform_copycontents;
    map<string, string> curlform_files;
    MODIO_DLL void setLogoPath(string logo_path);
    MODIO_DLL void setName(string name);
    MODIO_DLL void setHomepage(string homepage);
    MODIO_DLL void setSummary(string summary);
    MODIO_DLL void setPrice(double price);
    MODIO_DLL void setStock(int stock);
    MODIO_DLL void setDescription(string description);
    MODIO_DLL void setMetadata(string metadata);
    MODIO_DLL void setNameid(string nameid);
    MODIO_DLL void setModfile(int modfile);
  };
}

#endif
