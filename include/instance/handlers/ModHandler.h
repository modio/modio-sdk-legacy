#ifndef MODIO_MODHANDLER_H
#define MODIO_MODHANDLER_H

#include "extern_c/handlers/ModioModHandler.h"

namespace modio
{
  class MODIO_DLL ModHandler
  {
    ModioModHandler* mod_handler;
  public:
    ModHandler();
    void setLogoPath(const std::string& path);
    void setName(const std::string& name);
    void setHomepage(const std::string& homepage);
    void setSummary(const std::string& summary);
    void setDescription(const std::string& description);
    void setMetadataBlob(const std::string& metadata_blob);
    void setNameid(const std::string& name_id);
    void setModfile(int modfile);
    void addTag(const std::string& tag);
    ModioModHandler* getModioModHandler();
    ~ModHandler();
  };
}

#endif
