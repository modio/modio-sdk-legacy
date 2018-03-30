#ifndef MODIO_INSTANCE_H
#define MODIO_INSTANCE_H

#include "modio.h"
#include "c++/creators/FilterCreator.h"
#include "c++/creators/ModCreator.h"
#include "c++/creators/ModEditor.h"
#include "c++/creators/ModfileCreator.h"
#include "c++/creators/ModfileEditor.h"
#include "c++/schemas/Comment.h"
#include "c++/schemas/Dependency.h"
#include "c++/schemas/Filehash.h"
#include "c++/schemas/Game.h"
#include "c++/schemas/GameTagOption.h"
#include "c++/schemas/Image.h"
#include "c++/schemas/InstalledMod.h"
#include "c++/schemas/Media.h"
#include "c++/schemas/MetadataKVP.h"
#include "c++/schemas/Mod.h"
#include "c++/schemas/Event.h"
#include "c++/schemas/Modfile.h"
#include "c++/schemas/QueuedModDownload.h"
#include "c++/schemas/RatingSummary.h"
#include "c++/schemas/Response.h"
#include "c++/schemas/Tag.h"
#include "c++/schemas/User.h"
#include "c++/methods/callbacks/AuthenticationInstanceCallbacks.h"
#include "c++/methods/callbacks/CommentsInstanceCallbacks.h"
#include "c++/methods/callbacks/DependenciesInstanceCallbacks.h"
#include "c++/methods/callbacks/DownloadsInstanceCallbacks.h"
#include "c++/methods/callbacks/ImageInstanceCallbacks.h"
#include "c++/methods/callbacks/MeInstanceCallbacks.h"
#include "c++/methods/callbacks/MetadataKVPInstanceCallbacks.h"
#include "c++/methods/callbacks/ModfileInstanceCallbacks.h"
#include "c++/methods/callbacks/ModInstanceCallbacks.h"
#include "c++/methods/callbacks/ModEventsInstanceCallbacks.h"
#include "c++/methods/callbacks/TagsInstanceCallbacks.h"
#include "c++/methods/callbacks/SubscriptionInstanceCallbacks.h"
#include "c++/methods/callbacks/RatingsInstanceCallbacks.h"
#include "c++/methods/callbacks/ReportsInstanceCallbacks.h"

namespace modio
{
class MODIO_DLL Instance
{
  int current_call_id;

public:
  Instance(u32 environment, u32 id, const std::string &guid);

  //General Methods
  void sleep(u32 milliseconds);
  void process();

  //Events
  void getEvents(u32 mod_id, modio::FilterCreator &filter, const std::function<void(const modio::Response &, const std::vector<modio::Event> &events)> &callback);
  void getAllEvents(modio::FilterCreator &filter, const std::function<void(const modio::Response &, const std::vector<modio::Event> &events)> &callback);
  void setEventListener(const std::function<void(const modio::Response &, const std::vector<modio::Event> &events)> &callback);

  //Authentication Methods
  bool isLoggedIn() const;
  void logout() const;
  void setDebugLevel(u32 debug_level);
  void emailRequest(const std::string &email, const std::function<void(const modio::Response &)> &callback);
  void emailExchange(const std::string &security_code, const std::function<void(const modio::Response &)> &callback);

  //Media Methods
  void downloadImage(const std::string &image_url, const std::string &path, const std::function<void(const modio::Response &)> &callback);
  void editModLogo(u32 mod_id, const std::string &path, const std::function<void(const modio::Response &, u32 mod_id)> &callback);

  //Mod Methods
  void addMod(modio::ModCreator &mod_handler, const std::function<void(const modio::Response &response, const modio::Mod &mod)> &callback);
  void getMod(u32 mod_id, const std::function<void(const modio::Response &response, const modio::Mod &mod)> &callback);
  void getMods(modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Mod> &mods)> &callback);
  void editMod(u32 mod_id, modio::ModEditor &mod_handler, const std::function<void(const modio::Response &response, const modio::Mod &mod)> &callback);
  void deleteMod(u32 mod_id, const std::function<void(const modio::Response &response, u32 mod_id)> &callback);

  //Modfile Methods
  void getModfile(u32 mod_id, u32 modfile_id, const std::function<void(const modio::Response &response, const modio::Modfile &modfile)> &callback);
  void getModfiles(u32 mod_id, modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Modfile> &modfiles)> &callback);
  void addModfile(u32 mod_id, modio::ModfileCreator &modfile_handler, const std::function<void(const modio::Response &response, const modio::Modfile &modfile)> &callback);
  void editModfile(u32 mod_id, u32 modfile_id, modio::ModfileEditor &modfile_handler, const std::function<void(const modio::Response &response, const modio::Modfile &modfile)> &callback);

  //Tag Methods
  void getTags(u32 mod_id, const std::function<void(const modio::Response &response, std::vector<modio::Tag> tags)> &callback);
  void addTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response &response, u32 mod_id)> &callback);
  void deleteTags(u32 mod_id, std::vector<std::string> tags, const std::function<void(const modio::Response &response, u32 mod_id)> &callback);

  //Metadata KVP methods
  void getMetadataKVP(u32 mod_id, const std::function<void(const modio::Response &response, std::vector<modio::MetadataKVP> metadata_kvp)> &callback);
  void addMetadataKVP(u32 mod_id, std::vector<std::pair<std::string, std::string>> metadata_kvp, const std::function<void(const modio::Response &response)> &callback);
  void deleteMetadataKVP(u32 mod_id, std::vector<std::pair<std::string, std::string>> metadata_kvp, const std::function<void(const modio::Response &response)> &callback);

  //Ratings Methods
  void addModRating(u32 mod_id, bool vote_up, const std::function<void(const modio::Response &response)> &callback);

  //Subscription Methods
  void subscribeToMod(u32 mod_id, const std::function<void(const modio::Response &response, const modio::Mod &mod)> &callback);
  void unsubscribeFromMod(u32 mod_id, const std::function<void(const modio::Response &response)> &callback);

  //Me Methods
  void getAuthenticatedUser(const std::function<void(const modio::Response &response, const modio::User &user)> &callback);
  void getUserSubscriptions(modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Mod> &mods)> &callback);
  void getUserEvents(modio::FilterCreator &filter, const std::function<void(const modio::Response &, const std::vector<modio::Event> &events)> &callback);
  void getUserGames(modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Game> &games)> &callback);
  void getUserMods(modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Mod> &mods)> &callback);
  void getUserModfiles(modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Modfile> &modfiles)> &callback);

  //Downloads Methods
  void installMod(u32 mod_id);
  void uninstallMod(u32 mod_id);
  void pauseDownloads();
  void resumeDownloads();
  void prioritizeModDownload(u32 mod_id);  
  void setDownloadListener(const std::function<void(u32 response_code, u32 mod_id)> &callback);
  std::list<QueuedModDownload *> getModDownloadQueue();
  std::vector<modio::InstalledMod> getInstalledMods();
  u32 getModState(u32 mod_id);

  //Dependencies Methods
  void getAllModDependencies(u32 mod_id, const std::function<void(const modio::Response &response, const std::vector<modio::Dependency> &mods)> &callback);
  void addModDependencies(u32 mod_id, std::vector<u32> dependencies, const std::function<void(const modio::Response &response)> &callback);
  void deleteModDependencies(u32 mod_id, std::vector<u32> dependencies, const std::function<void(const modio::Response &response)> &callback);

  //Comments Methods
  void getAllModComments(u32 mod_id, modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Comment> &comments)> &callback);
  void deleteModComment(u32 mod_id, u32 comment_id, const std::function<void(const modio::Response &response)> &callback);

  //Reports Methods
  void submitReport(std::string resource, u32 id, u32 type, std::string name, std::string summary, const std::function<void(const modio::Response &response)> &callback);  
};
}

#endif
