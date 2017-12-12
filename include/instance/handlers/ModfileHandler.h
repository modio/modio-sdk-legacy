#ifndef MODIO_MODFILEHANDLER_H
#define MODIO_MODFILEHANDLER_H

#include "extern_c/handlers/ModioModfileHandler.h"

namespace modio
{
  class MODIO_DLL ModfileHandler
  {
    ModioModfileHandler* modfile_handler;
  public:
    ModfileHandler();
    void setPath(const std::string& path);
    void setVersion(const std::string& version);
    void setChangelog(const std::string& changelog);
    void setActive(bool active);
    ModioModfileHandler* getModioModfileHandler();
    ~ModfileHandler();
  };
}

#endif
