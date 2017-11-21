//#include "handlers_instace/ModfileHandlerInstance.h"
#include "ModIOSDK.h"

namespace modio
{
  class Filter
  {
    ModioFilter* filter;
  public:
    Filter();
    void setFilterSort(const std::string& field, bool ascending);
    void setFilterLimit(u32 limit);
    void setFilterOffset(u32 offset);
    void setFilterCursor(u32 cursor);
    void setFilterFullTextSearch(const std::string& text);
    void addFilterFieldValue(const std::string& field, const std::string& value);
    void addFilterLikeField(const std::string& field, const std::string& value);
    void addFilterNotLikeField(const std::string& field, const std::string& value);
    void addFilterInField(const std::string& field, const std::string& value);
    void addFilterNotInField(const std::string& field, const std::string& value);
    void addFilterMinField(const std::string& field, double value);
    void addFilterMaxField(const std::string& field, double value);
    void addFilterSmallerThanField(const std::string& field, double value);
    void addFilterGreaterThanField(const std::string& field, double value);
    void addFilterNotEqualField(const std::string& field, const std::string& value);
    ModioFilter* getFilter();
    ~Filter();
  };

  class Instance
  {
    int current_call_id;

  public:
    Instance(u32 id, const std::string& guid);

    //Authentication Methods
    bool isLoggedIn() const;
    void logout() const;
    bool emailRequest(void* object, const std::string& email, const std::function<void(void* object, const ModioResponse&, const std::string&)>& callback);
    bool emailExchange(void* object, const std::string& security_code, const std::function<void(void* object, const ModioResponse&)>& callback);

    //Media Methods
    bool downloadImage(void* object, const std::string& image_url, const std::string& path, const std::function<void(void* object, const ModioResponse&, const std::string& path)>& callback);
    bool editModLogo(void* object, u32 mod_id, const std::string& path, const std::function<void(void* object, const ModioResponse&, const int& mod_id)>& callback);

    //Mod Methods
    bool getMods(void* object, modio::Filter& filter, const std::function<void(void* object, const ModioResponse&, const std::vector<ModioMod*> & mods)>& callback);

    //Mod Methods
    //bool getMods(void* object, modio::Filter filter, const std::function<void(void* object, const ModioResponse&, std::vector<ModioMod*> mods)>& callback);
    /*
    void addMod(void* object, ModioModHandler mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod* mod));
    void editMod(void* object, int mod_id, ModioModHandler mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod* mod));
    void deleteMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, ModioMod* mod));
    void setUserModVote(void* object, int mod_id, bool vote_up, void (*callback)(void* object, ModioResponse response, int mod_id));
    void subscribeMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id));
    void unsubscribeMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id));
    */
  };
}
