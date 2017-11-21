#include "ModIOSDK.h"

namespace modio
{
  class ModfileHandler
  {
    ModioModfileHandler* modfile_handler;
  public:
    ModfileHandler();
    void setModfilePath(const std::string& path);
    void setModfileVersion(const std::string& version);
    void setModfileChangelog(const std::string& changelog);
    void setModfileActive(bool active);
    ~ModfileHandler();
  };
}
