#include "modio.h"

void loadEventPollingFile()
{
  modio::writeLogLine("Loading mod events data...", MODIO_DEBUGLEVEL_LOG);

  modio::LAST_MOD_EVENT_POLL = 0;

  nlohmann::json event_polling_json = modio::openJson(modio::getModIODirectory() + "event_polling.json");

  if (modio::hasKey(event_polling_json, "last_mod_event_poll"))
  {
    modio::LAST_MOD_EVENT_POLL = event_polling_json["last_mod_event_poll"];
    modio::writeLogLine("Mod events data loaded. The last mod event poll was at " + modio::toString(modio::LAST_MOD_EVENT_POLL), MODIO_DEBUGLEVEL_LOG);
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

  nlohmann::json token_file_json = modio::openJson(modio::getModIODirectory() + "authentication.json");

  if (modio::hasKey(token_file_json, "access_token"))
  {
    std::string access_token = token_file_json["access_token"];
    modio::ACCESS_TOKEN = access_token;

    modio::writeLogLine("Authentication token found. You are logged in.", MODIO_DEBUGLEVEL_LOG);

    if (modio::hasKey(token_file_json, "last_user_event_poll"))
    {
      modio::LAST_USER_EVENT_POLL = token_file_json["last_user_event_poll"];
      modio::writeLogLine("User events data loaded. The last user event poll was at " + modio::toString(modio::LAST_USER_EVENT_POLL), MODIO_DEBUGLEVEL_LOG);
    }
    else
    {
      modio::writeLogLine("No user events data found, downloading from the beginning.", MODIO_DEBUGLEVEL_LOG);
    }
  }
  else
  {
    modio::writeLogLine("Authentication token not found. You are not logged in.", MODIO_DEBUGLEVEL_LOG);
  }
}

void modioInit(u32 environment, u32 game_id, char const *api_key, char const *root_path)
{
  if (root_path)
    modio::ROOT_PATH = root_path;
  
  modio::createDirectory(modio::getModIODirectory());
  modio::createDirectory(modio::getModIODirectory() + "mods/");
  modio::createDirectory(modio::getModIODirectory() + "cache/");
  modio::createDirectory(modio::getModIODirectory() + "tmp/");

  modio::clearLog();

  modio::writeLogLine("Initializing SDK", MODIO_DEBUGLEVEL_LOG);
  if (root_path)
  {
    modio::writeLogLine(".modio/ directory created at " + std::string(root_path), MODIO_DEBUGLEVEL_LOG);
  }else
  {
    modio::writeLogLine(".modio/ directory created at current workspace.", MODIO_DEBUGLEVEL_LOG);
  }
  
  modio::writeLogLine("v0.11.3 DEV", MODIO_DEBUGLEVEL_LOG);

  if (environment == MODIO_ENVIRONMENT_TEST)
    modio::MODIO_URL = "https://api.test.mod.io/";
  modio::GAME_ID = game_id;
  modio::API_KEY = api_key;
  
  modio::installDownloadedMods();

  loadEventPollingFile();
  loadAuthenticationFile();

  modio::curlwrapper::initCurl();

  modioInitConfig();

  modio::updateInstalledModsJson();

  modio::clearOldCache();

  nlohmann::json authentication_json = modio::openJson(modio::getModIODirectory() + "authentication.json");
  if (modio::hasKey(authentication_json, "user"))
    modioInitUser(&modio::current_user, authentication_json["user"]);

  if (modioIsLoggedIn())
    modioGetAuthenticatedUser(NULL, &modio::onUpdateCurrentUser);

  modio::writeLogLine("SDK Initialized", MODIO_DEBUGLEVEL_LOG);
}

void modioSetDebugLevel(u32 debug_level)
{
  modio::DEBUG_LEVEL = debug_level;
}

void modioShutdown()
{
  modio::writeLogLine("mod.io C interface is shutting down", MODIO_DEBUGLEVEL_LOG);

  modio::curlwrapper::shutdownCurl();

  clearAuthenticationCallbackParams();
  clearCommentsCallbackParams();
  clearDependenciesCallbackParams();
  clearImageCallbackParams();
  clearMediaCallbackParams();
  clearMeCallbackParams();
  clearMetadataKVPCallbackParams();
  clearModEventCallbackParams();
  clearModfileCallbackParams();
  clearModCallbackParams();
  clearModStatsCallbackParams();
  clearRatingsCallbackParams();
  clearReportsCallbackParams();
  clearSubscriptionCallbackParams();
  clearTagCallbackParams();

  modioFreeUser(&modio::current_user);

  modio::writeLogLine("mod.io C interface finished shutting down", MODIO_DEBUGLEVEL_LOG);
}

void modioProcess()
{
  if (modio::AUTOMATIC_UPDATES == MODIO_UPDATES_ENABLED)
    modio::pollEvents();
  modio::curlwrapper::process();
}

void modioSleep(u32 milliseconds)
{
#if defined(MODIO_LINUX_DETECTED) || defined(MODIO_OSX_DETECTED)
  usleep(milliseconds * 1000);
#endif

#ifdef MODIO_WINDOWS_DETECTED
  Sleep(milliseconds);
#endif
}

void compressFiles(char const *root_directory, char const * const filenames[], u32 filenames_size, char const *zip_path)
{
  std::vector<std::string> filenames_vector;
  for (u32 i = 0; i < filenames_size; i++)
  {
    filenames_vector.push_back(filenames[i]);
  }
  modio::minizipwrapper::compressFiles(root_directory, filenames_vector, zip_path);
}
