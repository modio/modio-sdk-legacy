#ifndef MODIO_MODFILE_UPDATER_H
#define MODIO_MODFILE_UPDATER_H

#include "extern_c/handlers/ModioModfileUpdater.h"

namespace modio
{
  class MODIO_DLL ModfileUpdater
  {
    ModioModfileUpdater* modfile_updater;
  public:
    ModfileUpdater();
    void setVersion(const std::string& version);
    void setChangelog(const std::string& changelog);
    void setActive(bool active);
    ModioModfileUpdater* getModioModfileUpdater();
    ~ModfileUpdater();
  };
}

#endif
