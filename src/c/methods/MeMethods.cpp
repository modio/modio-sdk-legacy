#include <map>                                         // for map
#include <string>                                      // for operator+, string
#include "ModUtility.h"                                // for getCallFileFro...
#include "ModioUtility.h"                              // for addGameIdFilter
#include "wrappers/CurlWrapper.h"      // for get, getCallNu...
#include "c/ModioC.h"                       // for u32, ModioResp...
#include "Utility.h"       // for getHeaders
#include "c/creators/ModioFilterCreator.h"  // for getFilterString
#include "Globals.h"      // for API_KEY, MODIO...
#include "c/methods/callbacks/MeCallbacks.h"           // for GetUserGamesPa...
#include "dependencies/nlohmann/json.hpp"              // for json

extern "C"
{
  void modioGetAuthenticatedUser(void* object, void (*callback)(void* object, ModioResponse response, ModioUser user))
  {
    if(!modioIsLoggedIn())
    {
      modio::processLocalUnauthorizedRequestUserParam(object, callback);
      return;
    }

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_authenticated_user_callbacks[call_number] = new GetAuthenticatedUserParams;
    get_authenticated_user_callbacks[call_number]->callback = callback;
    get_authenticated_user_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetAuthenticatedUser);
  }

  void modioGetUserSubscriptionsFilterString(void* object, char const* filter_string, u32 cache_max_age_seconds, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size))
  {
    if(!callback)
    {
      modio::writeLogLine("NULL callback detected", MODIO_DEBUGLEVEL_ERROR);
      return;
    }

    std::string url_without_api_key = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/subscribed/?" + (filter_string ? filter_string : "");
    std::string url = url_without_api_key + "&api_key=" + modio::API_KEY;

    for(auto get_user_subscriptions_callbacks_iterator : get_user_subscriptions_callbacks)
    {
      if(get_user_subscriptions_callbacks_iterator.second->url == url_without_api_key)
      {
        modio::writeLogLine("Avoiding paralel call...", MODIO_DEBUGLEVEL_LOG);
        GetUserSubscriptionsParams* get_user_subscriptions_params = get_user_subscriptions_callbacks_iterator.second;
        get_user_subscriptions_params->callbacks.push_back(callback);
        get_user_subscriptions_params->objects.push_back(object);
        return;
      }
    }

    u32 call_number = modio::curlwrapper::getCallNumber();

    GetUserSubscriptionsParams* new_get_user_subscriptions_params = new GetUserSubscriptionsParams;
    get_user_subscriptions_callbacks[call_number] = new_get_user_subscriptions_params;
    new_get_user_subscriptions_params->url = url_without_api_key;
    new_get_user_subscriptions_params->is_cache = false;
    new_get_user_subscriptions_params->callbacks.push_back(callback);
    new_get_user_subscriptions_params->objects.push_back(object);

    std::string cache_filename = modio::getCallFileFromCache(url_without_api_key, cache_max_age_seconds);
    if(cache_filename != "")
    {
      modio::writeLogLine("Cache file found: " + cache_filename, MODIO_DEBUGLEVEL_LOG);
      nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache/" + cache_filename);
      if(!cache_file_json.empty())
      {
        new_get_user_subscriptions_params->is_cache = true;
        modioOnGetUserSubscriptions(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetUserSubscriptions);
  }

  void modioGetUserSubscriptions(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size))
  {
    if(!modioIsLoggedIn())
    {
      modio::processLocalUnauthorizedRequestModsParam(object, callback);
      return;
    }

    modio::addGameIdFilter(filter);

    std::string filter_string = modio::getFilterString(&filter);
    modioGetUserSubscriptionsFilterString(object, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }

  void modioGetUserEventsFilterString(void* object, char const* filter_string, u32 cache_max_age_seconds, void (*callback)(void* object, ModioResponse response, ModioUserEvent* events_array, u32 events_array_size))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/events?" + (filter_string ? filter_string : "") + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_user_events_callbacks[call_number] = new GetUserEventsParams;
    get_user_events_callbacks[call_number]->callback = callback;
    get_user_events_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetUserEvents);
  }

  void modioGetUserEvents(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioUserEvent* events_array, u32 events_array_size))
  {
    if(!modioIsLoggedIn())
    {
      modio::processLocalUnauthorizedRequestUserEventsParam(object, callback);
      return;
    }

    modio::addGameIdFilter(filter);
    
    std::string filter_string = modio::getFilterString(&filter);
    modioGetUserEventsFilterString(object, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }

  void modioGetUserGamesFilterString(void* object, char const* filter_string, u32 cache_max_age_seconds, void (*callback)(void* object, ModioResponse response, ModioGame games[], u32 games_size))
  {
    std::string url_without_api_key = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/games/?" + (filter_string ? filter_string : "");
    std::string url = url_without_api_key + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_user_games_callbacks[call_number] = new GetUserGamesParams;
    get_user_games_callbacks[call_number]->callback = callback;
    get_user_games_callbacks[call_number]->object = object;
    get_user_games_callbacks[call_number]->url = url_without_api_key;
    get_user_games_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url_without_api_key, cache_max_age_seconds);
    if(cache_filename != "")
    {
      nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache/" + cache_filename);
      if(!cache_file_json.empty())
      {
        get_user_games_callbacks[call_number]->is_cache = true;
        modioOnGetUserGames(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetUserGames);
  }

  void modioGetUserGames(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioGame games[], u32 games_size))
  {
    if(!modioIsLoggedIn())
    {
      modio::processLocalUnauthorizedRequestGamesParam(object, callback);
      return;
    }

    std::string filter_string = modio::getFilterString(&filter);
    modioGetUserGamesFilterString(object, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }

  void modioGetUserModsFilterString(void* object, char const* filter_string, u32 cache_max_age_seconds, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size))
  {
    std::string url_without_api_key = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/mods/?" + (filter_string ? filter_string : "");
    std::string url = url_without_api_key + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_user_mods_callbacks[call_number] = new GetUserModsParams;
    get_user_mods_callbacks[call_number]->callback = callback;
    get_user_mods_callbacks[call_number]->object = object;
    get_user_mods_callbacks[call_number]->url = url_without_api_key;
    get_user_mods_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url_without_api_key, cache_max_age_seconds);
    if(cache_filename != "")
    {
      nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache/" + cache_filename);
      if(!cache_file_json.empty())
      {
        get_user_mods_callbacks[call_number]->is_cache = true;
        modioOnGetUserMods(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetUserMods);
  }

  void modioGetUserMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size))
  {
    if(!modioIsLoggedIn())
    {
      modio::processLocalUnauthorizedRequestModsParam(object, callback);
      return;
    }

    modio::addGameIdFilter(filter);
    
    std::string filter_string = modio::getFilterString(&filter);
    modioGetUserModsFilterString(object, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }

  void modioGetUserModfilesFilterString(void* object, char const* filter_string, u32 cache_max_age_seconds, void (*callback)(void* object, ModioResponse response, ModioModfile modfiles[], u32 modfiles_size))
  {
    std::string url_without_api_key = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/files/?" + (filter_string ? filter_string : "");
    std::string url = url_without_api_key + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_user_modfiles_callbacks[call_number] = new GetUserModfilesParams;
    get_user_modfiles_callbacks[call_number]->callback = callback;
    get_user_modfiles_callbacks[call_number]->object = object;
    get_user_modfiles_callbacks[call_number]->url = url_without_api_key;
    get_user_modfiles_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url_without_api_key, cache_max_age_seconds);
    if(cache_filename != "")
    {
      nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache/" + cache_filename);
      if(!cache_file_json.empty())
      {
        get_user_modfiles_callbacks[call_number]->is_cache = true;
        modioOnGetUserModfiles(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetUserModfiles);
  }

  void modioGetUserModfiles(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioModfile modfiles[], u32 modfiles_size))
  {
    if(!modioIsLoggedIn())
    {
      modio::processLocalUnauthorizedRequestModfilesParam(object, callback);
      return;
    }

    modio::addGameIdFilter(filter);
    
    std::string filter_string = modio::getFilterString(&filter);
    modioGetUserModfilesFilterString(object, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }

  void modioGetUserRatingsFilterString(void* object, char const* filter_string, u32 cache_max_age_seconds, void (*callback)(void* object, ModioResponse response, ModioRating ratings[], u32 ratings_size))
  {
    std::string url_without_api_key = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/ratings/?" + (filter_string ? filter_string : "");
    std::string url = url_without_api_key + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_user_ratings_callbacks[call_number] = new GetUserRatingsParams;
    get_user_ratings_callbacks[call_number]->callback = callback;
    get_user_ratings_callbacks[call_number]->object = object;
    get_user_ratings_callbacks[call_number]->url = url_without_api_key;
    get_user_ratings_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url_without_api_key, cache_max_age_seconds);
    if(cache_filename != "")
    {
      nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache/" + cache_filename);
      if(!cache_file_json.empty())
      {
        get_user_ratings_callbacks[call_number]->is_cache = true;
        modioOnGetUserRatings(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetUserRatings);
  }

  void modioGetUserRatings(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioRating ratings[], u32 ratings_size))
  {
    if(!modioIsLoggedIn())
    {
      modio::processLocalUnauthorizedRequestRatingsParam(object, callback);
      return;
    }

    modio::addGameIdFilter(filter);
    
    std::string filter_string = modio::getFilterString(&filter);
    modioGetUserRatingsFilterString(object, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }

}
