#ifndef MODIO_INSTANCE_H
#define MODIO_INSTANCE_H

#include "modio.h"
#include "c++/creators/FilterCreator.h"
#include "c++/creators/ModCreator.h"
#include "c++/creators/ModEditor.h"
#include "c++/creators/ModfileCreator.h"
#include "c++/creators/ModfileEditor.h"
#include "c++/schemas/Error.h"
#include "c++/schemas/Filehash.h"
#include "c++/schemas/Image.h"
#include "c++/schemas/Media.h"
#include "c++/schemas/Mod.h"
#include "c++/schemas/Modfile.h"
#include "c++/schemas/RatingSummary.h"
#include "c++/schemas/Response.h"
#include "c++/schemas/Tag.h"
#include "c++/schemas/User.h"

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
    void setDebugLevel(u32 debug_level);
    void emailRequest(const std::string& email, const std::function<void(const modio::Response&)>& callback);
    void emailExchange(const std::string& security_code, const std::function<void(const modio::Response&)>& callback);

    //Media Methods
    void downloadImage(const std::string& image_url, const std::string& path, const std::function<void(const modio::Response&)>& callback);
    void editModLogo(u32 mod_id, const std::string& path, const std::function<void(const modio::Response&, u32 mod_id)>& callback);

    //Mod Methods
    void addMod(modio::ModCreator& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback);
    void getMod(u32 mod_id, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback);
    void getMods(modio::FilterCreator& filter, const std::function<void(const modio::Response& response, const std::vector<modio::Mod> & mods)>& callback);
    void getUserMods(modio::FilterCreator& filter, const std::function<void(const modio::Response& response, const std::vector<modio::Mod> & mods)>& callback);
    void editMod(u32 mod_id, modio::ModEditor& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback);
    void deleteMod(u32 mod_id, const std::function<void(const modio::Response& response, u32 mod_id)>& callback);

    //Modfile Methods
    void addModfile(u32 mod_id, modio::ModfileCreator& modfile_handler, const std::function<void(const modio::Response& response, const modio::Modfile& modfile)>& callback);
    void editModfile(u32 mod_id, u32 modfile_id, modio::ModfileEditor& modfile_handler, const std::function<void(const modio::Response& response, const modio::Modfile& modfile)>& callback);
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
