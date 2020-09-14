#include "modio.h"
#include "c/methods/callbacks/AuthenticationCallbacks.h"
#include "c/schemas/ModioUser.h"
#include "c/methods/callbacks/CommentsCallbacks.h"
#include "c/methods/callbacks/DependenciesCallbacks.h"
#include "c/methods/callbacks/ImageCallbacks.h"
#include "c/methods/callbacks/MediaCallbacks.h"
#include "c/methods/callbacks/MeCallbacks.h"
#include "c/methods/callbacks/MetadataKVPCallbacks.h"
#include "c/methods/callbacks/ModEventCallbacks.h"
#include "c/methods/callbacks/ModfileCallbacks.h"
#include "c/methods/callbacks/ModCallbacks.h"
#include "c/methods/callbacks/ModStatsCallbacks.h"
#include "c/methods/callbacks/RatingsCallbacks.h"
#include "c/methods/callbacks/ReportsCallbacks.h"
#include "c/methods/callbacks/SubscriptionsCallbacks.h"
#include "c/methods/callbacks/GameCallbacks.h"
#include "c/methods/callbacks/TagCallbacks.h"
#include <iostream>

#ifdef MODIO_LINUX_DETECTED
#include <unistd.h>
#endif

#ifdef MODIO_OSX_DETECTED
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#endif

#ifdef MODIO_WINDOWS_DETECTED
#  ifdef MODIO_UE4_DETECTED 
#    include <Windows/MinWindows.h>
#  else
#    include <windows.h>
#  endif
#endif

static void loadEventPollingFile()
{
  modio::writeLogLine("Loading mod events data...", MODIO_DEBUGLEVEL_LOG);

  modio::LAST_MOD_EVENT_POLL_ID = 0;

  nlohmann::json event_polling_json = modio::openJson(modio::getModIODirectory() + "event_polling.json");

  if (modio::hasKey(event_polling_json, "last_mod_event_poll_id"))
  {
    modio::LAST_MOD_EVENT_POLL_ID = event_polling_json["last_mod_event_poll_id"];
    modio::writeLogLine("Mod events data loaded. The last mod event id polled was " + modio::toString(modio::LAST_MOD_EVENT_POLL_ID), MODIO_DEBUGLEVEL_LOG);
  }
  else
  {
    modio::writeLogLine("No mod events data found, downloading from the beginning.", MODIO_DEBUGLEVEL_LOG);
  }
}

static void loadAuthenticationFile()
{
  modio::writeLogLine("Loading authentication data...", MODIO_DEBUGLEVEL_LOG);

  modio::ACCESS_TOKEN = "";
  modio::clearCache();
  modio::LAST_USER_EVENT_POLL_ID = 0;

  nlohmann::json token_file_json = modio::openJson(modio::getModIODirectory() + "authentication.json");

  if (modio::hasKey(token_file_json, "access_token"))
  {
    std::string access_token = token_file_json["access_token"];
    modio::ACCESS_TOKEN = access_token;

    modio::writeLogLine("Authentication token found. You are logged in.", MODIO_DEBUGLEVEL_LOG);

    if (modio::hasKey(token_file_json, "last_user_event_poll_id"))
    {
      modio::LAST_USER_EVENT_POLL_ID = token_file_json["last_user_event_poll_id"];
      modio::writeLogLine("User events data loaded. The last user event id polled was " + modio::toString(modio::LAST_USER_EVENT_POLL_ID), MODIO_DEBUGLEVEL_LOG);
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

void checkIfInstalledModsAreUpdated()
{
  modio::writeLogLine("Checking if all installed mods are updated...", MODIO_DEBUGLEVEL_LOG);

  u32 installed_mods_count = modioGetAllInstalledModsCount();
  if (installed_mods_count > 0)
  {
    ModioInstalledMod *installed_mods = new ModioInstalledMod[installed_mods_count];
    modioGetAllInstalledMods(installed_mods);

    u32 *mod_id_array = new u32[installed_mods_count];
	  for (size_t i = 0; i < installed_mods_count; i++)
		  mod_id_array[i] = installed_mods[i].mod_id;

    modioDownloadModfilesById(NULL, mod_id_array, installed_mods_count, &modio::onCheckIfInstalledModsAreUpdated);

    delete[] installed_mods;
    delete[] mod_id_array;
  }
  else
  {
    modio::writeLogLine("No mods installed. Skipping check.", MODIO_DEBUGLEVEL_LOG);
  }
}

void modioInit(u32 environment, u32 game_id, bool retrieve_mods_from_other_games, bool polling_enabled, char const *api_key, char const *root_path)
{
  std::clog << "[mod.io] Initializing mod.io SDK " << modio::VERSION << std::endl;
  srand (time(NULL));

  modio::RETRIEVE_MODS_FROM_OTHER_GAMES = retrieve_mods_from_other_games;
  modio::POLLING_ENABLED = polling_enabled;
  
  modio::ROOT_PATH = root_path ? root_path : "";
  
  std::clog << "[mod.io] Creating directories" << std::endl;

  modio::ADDITIONAL_GAMEDIR_PATH = "";

  if(!modio::createPath(modio::getModIODirectory()))
  {
    std::clog << "Could not create the .modio/ directory, retying with alternative path: " << modio::getMyDocumentsPath() << std::endl;
    modio::ROOT_PATH = modio::getMyDocumentsPath();
    modio::ADDITIONAL_GAMEDIR_PATH = "game_" + modio::toString(game_id);
    modio::createPath(modio::getModIODirectory());
  }
  modio::createPath(modio::getModIODirectory() + "mods/");
  modio::createPath(modio::getModIODirectory() + "cache/");
  modio::createPath(modio::getModIODirectory() + "tmp/");

  modio::clearLog();

  modio::writeLogLine("Initializing SDK", MODIO_DEBUGLEVEL_LOG);
  if (root_path)
  {
    modio::writeLogLine(".modio/ directory created at " + std::string(root_path), MODIO_DEBUGLEVEL_LOG);
  }else
  {
    modio::writeLogLine(".modio/ directory created at the game directory", MODIO_DEBUGLEVEL_LOG);
  }
  
  modio::writeLogLine(modio::VERSION, MODIO_DEBUGLEVEL_LOG);

  modio::MODIO_URL = environment == MODIO_ENVIRONMENT_LIVE ? "https://api.mod.io/" : "https://api.test.mod.io/";
  modio::GAME_ID = game_id;
  modio::API_KEY = api_key ? api_key : "";

  loadEventPollingFile();
  // This calls potentially setup modio::ACCESS_TOKEN from cached authentication data, so it has to be called before accessing that token
  loadAuthenticationFile();

  modio::curlwrapper::initCurl();

  modioInitConfig();

  modio::updateInstalledModsJson();
  modio::updateDownloadedModsJson();
  modio::installDownloadedMods();

  modio::clearCache();

  nlohmann::json authentication_json = modio::openJson(modio::getModIODirectory() + "authentication.json");
  if (modio::hasKey(authentication_json, "user"))
    modioInitUser(&modio::current_user, authentication_json["user"]);

  if (modio::ACCESS_TOKEN != "")
  {
    modioGetAuthenticatedUser(NULL, &modio::onUpdateCurrentUser);
    
    modio::updateUserRatings();
    modio::updateUserSubscriptions();
  }

  checkIfInstalledModsAreUpdated();

  modio::writeLogLine("SDK Initialized", MODIO_DEBUGLEVEL_LOG);
}

void modioSetDebugLevel(u32 debug_level)
{
  modio::DEBUG_LEVEL = debug_level;
}

void modioSetModEventsPollInterval(u32 interval_in_seconds)
{
  if(interval_in_seconds < modio::MOD_EVENT_MINIMUM_POLL_INTERVAL)
    interval_in_seconds = modio::MOD_EVENT_MINIMUM_POLL_INTERVAL;
  modio::MOD_EVENT_POLL_INTERVAL = interval_in_seconds;
}

void modioSetUserEventsPollInterval(u32 interval_in_seconds)
{
  if(interval_in_seconds < modio::USER_EVENT_MINIMUM_POLL_INTERVAL)
    interval_in_seconds = modio::USER_EVENT_MINIMUM_POLL_INTERVAL;
  modio::USER_EVENT_POLL_INTERVAL = interval_in_seconds;
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
  clearSubscriptionsCallbackParams();
  clearTagCallbackParams();
  clearGameCallbackParams();

  modioFreeUser(&modio::current_user);

  modio::writeLogLine("mod.io C interface finished shutting down", MODIO_DEBUGLEVEL_LOG);
}

void modioClearCache()
{
  modio::clearCache();
}

void modioPollEvents()
{
  u32 current_time = modio::getCurrentTimeSeconds();
  
  if(modioIsLoggedIn())
    modio::pollUserEvents(current_time);
  else
    modio::writeLogLine("User is not logged in, user events won't be polled.", MODIO_DEBUGLEVEL_LOG);

  if(modioGetAllInstalledModsCount() > 0)
    modio::pollInstalledModsEvents(current_time);
  else
    modio::writeLogLine("No mods are installed, mod events won't be polled.", MODIO_DEBUGLEVEL_LOG);
}

void modioProcess()
{
  if (modio::POLLING_ENABLED && modio::AUTOMATIC_UPDATES == MODIO_UPDATES_ENABLED)
  {
    u32 current_time = modio::getCurrentTimeSeconds();
    if (modioIsLoggedIn() && current_time - modio::LAST_USER_EVENT_POLL_TIME > modio::USER_EVENT_POLL_INTERVAL)
    {
      modio::clearCache();
      modio::pollUserEvents(current_time);
    }
    if (modioGetAllInstalledModsCount() > 0 && current_time - modio::LAST_MOD_EVENT_POLL_TIME > modio::MOD_EVENT_POLL_INTERVAL)
    {
      modio::clearCache();
      modio::pollInstalledModsEvents(current_time);
    }
  }
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

void extractFiles(char const* zip_path, char const* directory_path)
{
  modio::minizipwrapper::extract(zip_path, directory_path);
}

void windowsUTF8ToAnsi(const char* UTF8_string, char* ansi_string)
{
  #ifdef MODIO_WINDOWS_DETECTED
    char* utf8_char = (char*)UTF8_string;
    int length = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)utf8_char, -1, NULL, 0);
    if (length > 0)
    {
      wchar_t* wide = new wchar_t[length];
      MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)utf8_char, -1, wide, length);

      size_t convertedChars = 0;
      wcstombs_s(&convertedChars, ansi_string, length, wide, _TRUNCATE);
      std::string return_value = ansi_string;
      delete[] wide;
    }
  #endif
}