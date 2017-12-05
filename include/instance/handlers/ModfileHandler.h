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
    void setModfilePath(const std::string& path);
    void setModfileVersion(const std::string& version);
    void setModfileChangelog(const std::string& changelog);
    void setModfileActive(bool active);
    ModioModfileHandler* getModioModfileHandler();
    ~ModfileHandler();
  };
}

#endif
