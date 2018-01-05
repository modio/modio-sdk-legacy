#ifndef MODIO_INSTANCE_H
#define MODIO_INSTANCE_H

#include "ModIOSDK.h"
#include "instance/handlers/FilterHandler.h"
#include "instance/handlers/ModHandler.h"
#include "instance/handlers/ModfileHandler.h"
#include "instance/schemas/Error.h"
#include "instance/schemas/Filehash.h"
#include "instance/schemas/Image.h"
#include "instance/schemas/Media.h"
#include "instance/schemas/Mod.h"
#include "instance/schemas/Modfile.h"
#include "instance/schemas/RatingSummary.h"
#include "instance/schemas/Response.h"
#include "instance/schemas/Tag.h"
#include "instance/schemas/User.h"

namespace modio
{
  class MODIO_DLL Instance
  {
    int current_call_id;

  public:
    Instance(u32 id, const std::string& guid);

    //General Methods
    void sleep(u32 milliseconds);

    //Authentication Methods
    bool isLoggedIn() const;
    void logout() const;
    void emailRequest(const std::string& email, const std::function<void(const modio::Response&)>& callback);
    void emailExchange(const std::string& security_code, const std::function<void(const modio::Response&)>& callback);

    //Media Methods
    void downloadImage(const std::string& image_url, const std::string& path, const std::function<void(const modio::Response&)>& callback);
    void editModLogo(u32 mod_id, const std::string& path, const std::function<void(const modio::Response&, u32 mod_id)>& callback);

    //Mod Methods
    void addMod(modio::ModHandler& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback);
    void getMods(modio::FilterHandler& filter, const std::function<void(const modio::Response& response, const std::vector<modio::Mod> & mods)>& callback);
    void editMod(u32 mod_id, modio::ModHandler& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback);
    void deleteMod(u32 mod_id, const std::function<void(const modio::Response& response, u32 mod_id)>& callback);

    //Modfile Methods
    void addModfile(u32 mod_id, modio::ModfileHandler& modfile_handler, const std::function<void(const modio::Response& response, const modio::Modfile& modfile)>& callback);
    void editModfile(u32 mod_id, u32 modfile_id, modio::ModfileHandler& modfile_handler, const std::function<void(const modio::Response& response, const modio::Modfile& modfile)>& callback);
    void installModfile(modio::Modfile modfile, const std::string& destination_path, const std::function<void(const modio::Response& response)>& callback);
    u32 getModfileState(u32 modfile_id);
    double getModfileDownloadPercentage(u32 modfile_id);
    bool uninstallModfile(u32 modfile_id);
    std::vector<u32> getInstalledModfileIds();

    //Tag Methods
    void getTags(u32 mod_id, const std::function<void(const modio::Response& response, std::vector<modio::Tag> tags)>& callback);
    void addTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response& response, u32 mod_id)>& callback);
    void deleteTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response& response, u32 mod_id)>& callback);
  };
}

#endif
