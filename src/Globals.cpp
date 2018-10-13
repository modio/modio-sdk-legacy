#include "Globals.h"

namespace modio
{
  std::string API_KEY;
  std::string ACCESS_TOKEN = "";
  u32 GAME_ID;
  std::string ROOT_PATH = "";
  u32 DEBUG_LEVEL = MODIO_DEBUGLEVEL_LOG;
  std::string MODIO_URL = "https://api.mod.io/";
  std::string MODIO_VERSION_PATH = "v1/";
  u32 LAST_MOD_EVENT_POLL = 0;
  u32 LAST_USER_EVENT_POLL = 0;
  u32 EVENT_POLL_INTERVAL = 15;
  u32 RETRY_AFTER = 0;
  u32 MAX_CACHE_TIME = 3600;
  void (*event_listener_callback)(ModioResponse response, ModioEvent* events_array, u32 events_array_size) = NULL;
  void (*download_callback)(u32 response_code, u32 mod_id) = NULL;
  void (*upload_callback)(u32 response_code, u32 mod_id) = NULL;
  u32 AUTOMATIC_UPDATES = 0;
  u32 BACKGROUND_DOWNLOADS = 0;
  nlohmann::json installed_mods;
}
