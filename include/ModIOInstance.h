#include "ModIOSDK.h"
#include "handlers_instance/FilterHandler.h"
#include "handlers_instance/ModHandler.h"
#include "handlers_instance/ModfileHandler.h"
#include "instance_data_containers/Error.h"
#include "instance_data_containers/Filehash.h"
#include "instance_data_containers/Image.h"
#include "instance_data_containers/Media.h"
#include "instance_data_containers/Mod.h"
#include "instance_data_containers/Modfile.h"
#include "instance_data_containers/RatingSummary.h"
#include "instance_data_containers/Response.h"
#include "instance_data_containers/Tag.h"
#include "instance_data_containers/User.h"

namespace modio
{
  class MODIO_DLL Instance
  {
    int current_call_id;

  public:
    Instance(u32 id, const std::string& guid);

    //Authentication Methods
    bool isLoggedIn() const;
    void logout() const;
    void emailRequest(const std::string& email, const std::function<void(const modio::Response&, const std::string&)>& callback);
    void emailExchange(const std::string& security_code, const std::function<void(const modio::Response&)>& callback);

    //Media Methods
    void downloadImage(const std::string& image_url, const std::string& path, const std::function<void(const modio::Response&, const std::string& path)>& callback);
    void editModLogo(u32 mod_id, const std::string& path, const std::function<void(const modio::Response&, u32 mod_id)>& callback);

    //Mod Methods
    void addMod(modio::ModHandler& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback);
    void getMods(modio::FilterHandler& filter, const std::function<void(const modio::Response& response, const std::vector<modio::Mod> & mods)>& callback);
    void editMod(u32 mod_id, modio::ModHandler& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback);
    void deleteMod(u32 mod_id, const std::function<void(const modio::Response& response, u32 mod_id)>& callback);

    //Modfile Methods
    void addModfile(u32 mod_id, modio::ModfileHandler& modfile_handler, const std::function<void(const modio::Response& response, const modio::Modfile& modfile)>& callback);
    void editModfile(u32 mod_id, u32 modfile_id, modio::ModfileHandler& modfile_handler, const std::function<void(const modio::Response& response, const modio::Modfile& modfile)>& callback);
    void installModfile(modio::Modfile modfile, const std::string& destination_path, const std::function<void(const modio::Response& response, const std::string& path)>& callback);
    u32 getModfileState(u32 modfile_id);
    double getModfileDownloadPercentage(u32 modfile_id);

    //Tag Methods
    void getTags(u32 mod_id, const std::function<void(const modio::Response& response, std::vector<modio::Tag> tags)>& callback);
    void addTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response& response, u32 mod_id, std::vector<modio::Tag> tags)>& callback);
    void deleteTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response& response, u32 mod_id, std::vector<modio::Tag> tags)>& callback);
  };
}
