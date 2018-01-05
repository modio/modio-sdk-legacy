#ifndef MODIO_MOD_UPDATER_H
#define MODIO_MOD_UPDATER_H

#include "extern_c/handlers/ModioModUpdater.h"

namespace modio
{
  class MODIO_DLL ModUpdater
  {
    ModioModUpdater* mod_updater;
  public:
    ModUpdater();
    void setName(const std::string& name);
    void setNameid(const std::string& name_id);
    void setSummary(const std::string& summary);
    void setDescription(const std::string& description);
    void setHomepage(const std::string& homepage);
    void setModfile(u32 modfile);
    void setMetadataBlob(const std::string& metadata_blob);
    void setStatus(u32 status);
    ModioModUpdater* getModioModUpdater();
    ~ModUpdater();
  };
}

#endif
