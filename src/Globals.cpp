#include "Globals.h"

namespace modio
{
  std::string API_KEY;
  std::string ACCESS_TOKEN = "";
  u32 GAME_ID;
  std::string ROOT_PATH = "";
  //u32 DEBUG_LEVEL = MODIO_DEBUGLEVEL_ERROR;
  u32 DEBUG_LEVEL = MODIO_DEBUGLEVEL_LOG;
  std::string MODIO_URL = "https://api.mod.io/";
  std::string MODIO_VERSION_PATH = "v1/";
  u32 MAX_CALL_CACHE = 10;
  u32 LAST_MOD_EVENT_POLL = 0;
  u32 LAST_USER_EVENT_POLL = 0;
  u32 EVENT_POLL_INTERVAL = 15;
  u32 RETRY_AFTER = 0;
  void (*callback)(ModioResponse response, ModioEvent* events_array, u32 events_array_size) = NULL;
  void (*download_callback)(u32 response_code, u32 mod_id) = NULL;
  void (*upload_callback)(u32 response_code, u32 mod_id) = NULL;
  u32 AUTOMATIC_UPDATES = 0;
  u32 BACKGROUND_DOWNLOADS = 0;

  std::vector<std::string> getHeaders()
  {
    std::vector<std::string> headers;
    if(modio::ACCESS_TOKEN != "")
      headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    return headers;
  }

  std::vector<std::string> getUrlEncodedHeaders()
  {
    std::vector<std::string> headers;
    if(modio::ACCESS_TOKEN != "")
      headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    headers.push_back("Content-Type: application/x-www-form-urlencoded");
    return headers;
  }
}
