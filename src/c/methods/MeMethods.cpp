#include "c/methods/MeMethods.h"

extern "C"
{
  void modioGetAuthenticatedUser(void* object, void (*callback)(void* object, ModioResponse response, ModioUser user))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_authenticated_user_callbacks[call_number] = new GetAuthenticatedUserParams;
    get_authenticated_user_callbacks[call_number]->callback = callback;
    get_authenticated_user_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetAuthenticatedUser);
  }

  void modioGetUserSubscriptions(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/subscribed/?" + filter_string + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_user_subscriptions_callbacks[call_number] = new GetUserSubscriptionsParams;
    get_user_subscriptions_callbacks[call_number]->callback = callback;
    get_user_subscriptions_callbacks[call_number]->object = object;
    get_user_subscriptions_callbacks[call_number]->url = url;
    get_user_subscriptions_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url, filter.cache_max_age_seconds);
    if(cache_filename != "")
    {
      std::ifstream cache_file(modio::getModIODirectory() + "cache/" + cache_filename);
      json cache_file_json;
      if(cache_file.is_open())
      {
        cache_file >> cache_file_json;
        get_user_subscriptions_callbacks[call_number]->is_cache = true;
        modioOnGetUserSubscriptions(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetUserSubscriptions);
  }

  void modioGetUserGames(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioGame games[], u32 games_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/games/?" + filter_string + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_user_games_callbacks[call_number] = new GetUserGamesParams;
    get_user_games_callbacks[call_number]->callback = callback;
    get_user_games_callbacks[call_number]->object = object;
    get_user_games_callbacks[call_number]->url = url;
    get_user_games_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url, filter.cache_max_age_seconds);
    if(cache_filename != "")
    {
      std::ifstream cache_file(modio::getModIODirectory() + "cache/" + cache_filename);
      json cache_file_json;
      if(cache_file.is_open())
      {
        cache_file >> cache_file_json;
        get_user_games_callbacks[call_number]->is_cache = true;
        modioOnGetUserGames(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetUserGames);
  }

  void modioGetUserMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/mods/?" + filter_string + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_user_mods_callbacks[call_number] = new GetUserModsParams;
    get_user_mods_callbacks[call_number]->callback = callback;
    get_user_mods_callbacks[call_number]->object = object;
    get_user_mods_callbacks[call_number]->url = url;
    get_user_mods_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url, filter.cache_max_age_seconds);
    if(cache_filename != "")
    {
      std::ifstream cache_file(modio::getModIODirectory() + "cache/" + cache_filename);
      json cache_file_json;
      if(cache_file.is_open())
      {
        cache_file >> cache_file_json;
        get_user_mods_callbacks[call_number]->is_cache = true;
        modioOnGetUserMods(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetUserMods);
  }

  void modioGetUserModfiles(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioModfile modfiles[], u32 modfiles_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/files/?" + filter_string + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_user_modfiles_callbacks[call_number] = new GetUserModfilesParams;
    get_user_modfiles_callbacks[call_number]->callback = callback;
    get_user_modfiles_callbacks[call_number]->object = object;
    get_user_modfiles_callbacks[call_number]->url = url;
    get_user_modfiles_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url, filter.cache_max_age_seconds);
    if(cache_filename != "")
    {
      std::ifstream cache_file(modio::getModIODirectory() + "cache/" + cache_filename);
      json cache_file_json;
      if(cache_file.is_open())
      {
        cache_file >> cache_file_json;
        get_user_modfiles_callbacks[call_number]->is_cache = true;
        modioOnGetUserModfiles(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetUserModfiles);
  }
}
