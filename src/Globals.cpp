#include "Globals.h"

namespace modio
{
  std::string API_KEY;
  std::string ACCESS_TOKEN = "";
  int GAME_ID;
  std::string ROOT_PATH = "";
  unsigned int DEBUG_LEVEL = MODIO_DEBUGLEVEL_ERROR;
  std::string MODIO_URL = "https://api.mod.io/";
  std::string MODIO_VERSION_PATH = "v1/";
  u32 MAX_CALL_CACHE = 10;
  u32 LAST_EVENT_POLL = 0;
  void (*callback)(ModioResponse response, ModioModEvent* mod_events_array, u32 mod_events_array_size) = NULL;
}
