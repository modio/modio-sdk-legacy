#include "ModIOSDK.h"

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
    void setPrice(double price);
    void setStock(int stock);
    void setDescription(const std::string& description);
    void setMetadata(const std::string& metadata);
    void setNameid(const std::string& nameid);
    void setModfile(int modfile);
    void addTag(const std::string& tag);
    ModioModHandler* getModioModHandler();
    ~ModHandler();
  };
}
