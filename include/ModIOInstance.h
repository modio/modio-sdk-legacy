//#include "handlers_instace/ModfileHandlerInstance.h"
#include "ModIOSDK.h"
#include "handlers_instance/ModHandlerInstance.h"
#include "handlers_instance/ModfileHandlerInstance.h"
#include "instance_data_containers/Error.h"
#include "instance_data_containers/Filehash.h"
#include "instance_data_containers/Image.h"
#include "instance_data_containers/Media.h"
#include "instance_data_containers/Mod.h"
#include "instance_data_containers/Modfile.h"
#include "instance_data_containers/Ratings.h"
#include "instance_data_containers/Response.h"
#include "instance_data_containers/Tag.h"
#include "instance_data_containers/User.h"

namespace modio
{
  class MODIO_DLL Filter
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

  class MODIO_DLL Instance
  {
    int current_call_id;

  public:
    Instance(u32 id, const std::string& guid);

    //Authentication Methods
    bool isLoggedIn() const;
    void logout() const;
    bool emailRequest(void* object, const std::string& email, const std::function<void(void* object, const modio::Response&, const std::string&)>& callback);
    bool emailExchange(void* object, const std::string& security_code, const std::function<void(void* object, const modio::Response&)>& callback);

    //Media Methods
    bool downloadImage(void* object, const std::string& image_url, const std::string& path, const std::function<void(void* object, const modio::Response&, const std::string& path)>& callback);
    bool editModLogo(void* object, u32 mod_id, const std::string& path, const std::function<void(void* object, const modio::Response&, u32 mod_id)>& callback);

    //Mod Methods
    void addMod(void* object, modio::ModHandler& mod_handler, const std::function<void(void* object, const modio::Response& response, const modio::Mod& mod)>& callback);
    bool getMods(void* object, modio::Filter& filter, const std::function<void(void* object, const modio::Response& response, const std::vector<modio::Mod> & mods)>& callback);
    void editMod(void* object, u32 mod_id, modio::ModHandler& mod_handler, const std::function<void(void* object, const modio::Response& response, const modio::Mod& mod)>& callback);
    void deleteMod(void* object, u32 mod_id, const std::function<void(void* object, const modio::Response& response, u32 mod_id)>& callback);

    //Modfile Methods
    void addModfile(void* object, u32 mod_id, modio::ModfileHandler& modfile_handler, const std::function<void(void* object, const modio::Response& response, const modio::Modfile& modfile)>& callback);
    void editModfile(void* object, u32 mod_id, u32 modfile_id, modio::ModfileHandler& modfile_handler, const std::function<void(void* object, const modio::Response& response, const modio::Modfile& modfile)>& callback);
    void installModfile(void* object, modio::Modfile modfile, const std::string& destination_path, const std::function<void(void* object, const modio::Response& response, const std::string& path)>& callback);
    u32 getModfileState(u32 modfile_id);
    double getModfileDownloadPercentage(u32 modfile_id);

    //Tag Methods
    void getTags(void* object, u32 mod_id, const std::function<void(void* object, const modio::Response& response, std::vector<modio::Tag> tags)>& callback);
    void addTags(void* object, u32 mod_id, std::vector<std::string> tags, const std::function<void(void* object, const modio::Response& response, u32 mod_id, std::vector<modio::Tag> tags)>& callback);
    void deleteTags(void* object, u32 mod_id, std::vector<std::string> tags, const std::function<void(void* object, const modio::Response& response, u32 mod_id, std::vector<modio::Tag> tags)>& callback);
  };
}
