#include "modio.h"

void modioInit(u32 environment, u32 game_id, char* api_key)
{
  u32 current_time = modio::getCurrentTime();
  modio::LAST_MOD_EVENT_POLL = current_time;
  modio::LAST_USER_EVENT_POLL = current_time;

  json installed_mods_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");
  if(modio::hasKey(installed_mods_json,"last_user_event_poll"))
    modio::LAST_USER_EVENT_POLL = installed_mods_json["last_user_event_poll"];
  if(modio::hasKey(installed_mods_json,"last_mod_event_poll"))
    modio::LAST_MOD_EVENT_POLL = installed_mods_json["last_mod_event_poll"];

  if(environment == MODIO_ENVIRONMENT_TEST)
  {
    modio::MODIO_URL = "https://api.test.mod.io/";
  }
  modio::clearLog();

  modio::curlwrapper::initCurl();

  modioInitConfig();

  modio::writeLogLine("Initializing SDK", MODIO_DEBUGLEVEL_LOG);
  modio::GAME_ID = game_id;

  modio::API_KEY = api_key;
  modio::ACCESS_TOKEN = "";

  json token_file_json = modio::openJson(modio::getModIODirectory() + "token.json");

  if(modio::hasKey(token_file_json,"access_token"))
  {
    std::string access_token = token_file_json["access_token"];
    modio::ACCESS_TOKEN = access_token;
  }

  modio::updateInstalledModsJson();

  /*
  if(modio::AUTOMATIC_UPDATES == MODIO_UPDATES_ENABLED)
  {
    modio::checkForInstalledModsUpdates();  
  }
  */

  modio::createDirectory(modio::getModIODirectory());
  modio::createDirectory(modio::getModIODirectory() + "mods/");
  modio::createDirectory(modio::getModIODirectory() + "cache/");
  modio::createDirectory(modio::getModIODirectory() + "tmp/");
  modio::writeLogLine("SDK Initialized", MODIO_DEBUGLEVEL_LOG);
}
/*
void init(int game_id, char* api_key, char* root_path)
{
  ROOT_PATH = root_path;
  init(game_id, api_key);
}
*/

void modioSetDebugLevel(unsigned int debug_level)
{
  modio::DEBUG_LEVEL = debug_level;
}

void modioShutdown()
{
  modio::curlwrapper::shutdownCurl();
}

void modioProcess()
{
  if(modio::AUTOMATIC_UPDATES == MODIO_UPDATES_ENABLED)
    modio::pollEvents();
  modio::curlwrapper::process();
}

void modioSleep(u32 milliseconds)
{
  #ifdef LINUX
    usleep(milliseconds * 1000);
  #endif
  #ifdef WINDOWS
    Sleep(milliseconds);
  #endif
  #ifdef OSX
    usleep(milliseconds * 1000);
  #endif
}
