#include "Globals.h"
#include <stddef.h>  // for NULL

namespace modio
{
  std::string VERSION = "v0.12.5 DEV";
  std::string API_KEY;
  std::string ACCESS_TOKEN = "";
  bool IS_LOGGED_IN = false;
  u32 GAME_ID;
  std::string ROOT_PATH = "";
  u32 DEBUG_LEVEL = MODIO_DEBUGLEVEL_LOG;
  bool RETRIEVE_MODS_FROM_OTHER_GAMES = false;
  std::string MODIO_URL = "https://api.mod.io/";
  std::string MODIO_VERSION_PATH = "v1/";
  u32 LAST_MOD_EVENT_POLL_ID = 0;
  u32 LAST_MOD_EVENT_POLL_TIME = 0;
  u32 MOD_EVENT_POLL_INTERVAL = 120;
  u32 LAST_USER_EVENT_POLL_ID = 0;
  u32 LAST_USER_EVENT_POLL_TIME = 0;
  u32 USER_EVENT_POLL_INTERVAL = 15;
  u32 EVENT_POLL_INTERVAL = 15;
  u32 RETRY_AFTER = 0;
  u32 MAX_CACHE_TIME_SECONDS = 120;
  ModioUser current_user;
  std::vector<u32> downloaded_mods;
  std::map<u32,u32> current_user_ratings; // maps[mod_id, rating_type]
  std::set<u32> current_user_subscriptions; // set[mod_id]
  void (*event_listener_callback)(ModioResponse response, ModioModEvent* events_array, u32 events_array_size) = NULL;
  void (*download_callback)(u32 response_code, u32 mod_id) = NULL;
  void (*upload_callback)(u32 response_code, u32 mod_id) = NULL;
  u32 AUTOMATIC_UPDATES = 0;
  u32 BACKGROUND_DOWNLOADS = 0;
  nlohmann::json installed_mods;
}
