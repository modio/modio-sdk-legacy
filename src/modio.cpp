#include "modio.h"

void loadInstalledModsFile()
{
  modio::writeLogLine("Loading mod events data...", MODIO_DEBUGLEVEL_LOG);

  modio::LAST_MOD_EVENT_POLL = 0;
  
  json installed_mods_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");

  if(modio::hasKey(installed_mods_json,"last_mod_event_poll"))
  {
    modio::LAST_MOD_EVENT_POLL = installed_mods_json["last_mod_event_poll"];
    modio::writeLogLine("Mod events data loaded. The last mod event poll was at " +  modio::toString(modio::LAST_MOD_EVENT_POLL), MODIO_DEBUGLEVEL_LOG);
  }
  else
  {
    modio::writeLogLine("No mod events data found, downloading from the beginning.", MODIO_DEBUGLEVEL_LOG);    
  }
}

void loadAuthenticationFile()
{
  modio::writeLogLine("Loading authentication data...", MODIO_DEBUGLEVEL_LOG);

  modio::ACCESS_TOKEN = "";
  modio::LAST_USER_EVENT_POLL = 0;

  json token_file_json = modio::openJson(modio::getModIODirectory() + "authentication.json");

  if(modio::hasKey(token_file_json,"access_token"))
  {
    std::string access_token = token_file_json["access_token"];
    modio::ACCESS_TOKEN = access_token;

    modio::writeLogLine("Authentication token found. You are logged in.", MODIO_DEBUGLEVEL_LOG);

    if(modio::hasKey(token_file_json,"last_user_event_poll"))
    {
      modio::LAST_USER_EVENT_POLL = token_file_json["last_user_event_poll"];
      modio::writeLogLine("User events data loaded. The last user event poll was at " +  modio::toString(modio::LAST_USER_EVENT_POLL), MODIO_DEBUGLEVEL_LOG);
    }
    else
    {
      modio::writeLogLine("No user events data found, downloading from the beginning.", MODIO_DEBUGLEVEL_LOG);
    }
  }else
  {
    modio::writeLogLine("Authentication token not found. You are not logged in.", MODIO_DEBUGLEVEL_LOG);
  }
}

void modioInit(u32 environment, u32 game_id, char* api_key, char* root_path)
{
  modio::clearLog();

  modio::writeLogLine("Initializing SDK", MODIO_DEBUGLEVEL_LOG);

  modio::createDirectory(modio::getModIODirectory());
  modio::createDirectory(modio::getModIODirectory() + "mods/");
  modio::createDirectory(modio::getModIODirectory() + "cache/");
  modio::createDirectory(modio::getModIODirectory() + "tmp/");
  
  if(environment == MODIO_ENVIRONMENT_TEST)
    modio::MODIO_URL = "https://api.test.mod.io/";
  modio::GAME_ID = game_id;
  modio::API_KEY = api_key;
  if(root_path)
    modio::ROOT_PATH = root_path;

  loadInstalledModsFile();
  loadAuthenticationFile();

  modio::curlwrapper::initCurl();

  modioInitConfig();

  modio::updateInstalledModsJson();

  modio::writeLogLine("SDK Initialized", MODIO_DEBUGLEVEL_LOG);
}
/*
void init(int game_id, char* api_key, char* root_path)
{
  ROOT_PATH = root_path;
  init(game_id, api_key);
}
*/

void modioSetDebugLevel(u32 debug_level)
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
