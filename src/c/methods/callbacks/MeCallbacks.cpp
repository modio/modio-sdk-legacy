#include "c/methods/callbacks/MeCallbacks.h"
#include "Utility.h"                // for hasKey
#include "c/schemas/ModioModfile.h" // for modioInitModfile ...

std::map<u32, GetAuthenticatedUserParams *> get_authenticated_user_callbacks;
std::map<u32, GetUserSubscriptionsParams *> get_user_subscriptions_callbacks;
std::map<u32, GetUserEventsParams *> get_user_events_callbacks;
std::map<u32, GetUserGamesParams *> get_user_games_callbacks;
std::map<u32, GetUserModsParams *> get_user_mods_callbacks;
std::map<u32, GetUserModfilesParams *> get_user_modfiles_callbacks;
std::map<u32, GetUserRatingsParams *> get_user_ratings_callbacks;

void modioOnGetAuthenticatedUser(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  modioInitUser(&modio::current_user, response_json);

  if(response_code >= 200 && response_code < 300)
  {
    nlohmann::json authentication_json = modio::openJson(modio::getModIODirectory() + "authentication.json");
    authentication_json["user"] = response_json;
    modio::writeJson(modio::getModIODirectory() + "authentication.json", authentication_json);
  }else if(response_code >= 401)
  {
    modioLogout();
  }
  

  get_authenticated_user_callbacks[call_number]->callback(get_authenticated_user_callbacks[call_number]->object, response, modio::current_user);

  delete get_authenticated_user_callbacks[call_number];
  get_authenticated_user_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnGetUserSubscriptions(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  u32 mods_size = 0;
  ModioMod *mods = NULL;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      if (!get_user_subscriptions_callbacks[call_number]->is_cache)
        modio::addCallToCache(get_user_subscriptions_callbacks[call_number]->url, response_json);

      mods_size = (u32)response_json["data"].size();
      mods = new ModioMod[mods_size];
      for (u32 i = 0; i < mods_size; i++)
        modioInitMod(&mods[i], response_json["data"][i]);
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  for(int i=0; i<get_user_subscriptions_callbacks[call_number]->callbacks.size(); i++)
  {
    get_user_subscriptions_callbacks[call_number]->callbacks[i](get_user_subscriptions_callbacks[call_number]->objects[i], response, mods, mods_size);
  }

  delete get_user_subscriptions_callbacks[call_number];
  get_user_subscriptions_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < mods_size; i++)
    modioFreeMod(&mods[i]);
  if (mods)
    delete[] mods;
}

void modioOnGetUserEvents(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  ModioUserEvent *events_array = NULL;
  u32 events_array_size = 0;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      events_array_size = (u32)response_json["data"].size();
      events_array = new ModioUserEvent[events_array_size];

      for (u32 i = 0; i < events_array_size; i++)
        modioInitUserEvent(&(events_array[i]), response_json["data"][i]);
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  get_user_events_callbacks[call_number]->callback(get_user_events_callbacks[call_number]->object, response, events_array, events_array_size);

  delete get_user_events_callbacks[call_number];
  get_user_events_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < events_array_size; i++)
    modioFreeUserEvent(&(events_array[i]));
  if (events_array)
    delete[] events_array;
}

void modioOnGetUserGames(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  ModioGame *games = NULL;
  u32 games_size = 0;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      if (!get_user_games_callbacks[call_number]->is_cache)
        modio::addCallToCache(get_user_games_callbacks[call_number]->url, response_json);

      games_size = (u32)response_json["data"].size();
      games = new ModioGame[games_size];
      for (u32 i = 0; i < games_size; i++)
        modioInitGame(&games[i], response_json["data"][i]);
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  get_user_games_callbacks[call_number]->callback(get_user_games_callbacks[call_number]->object, response, games, games_size);

  delete get_user_games_callbacks[call_number];
  get_user_games_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < games_size; i++)
    modioFreeGame(&games[i]);
  if (games)
    delete[] games;
}

void modioOnGetUserMods(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  u32 mods_size = 0;
  ModioMod *mods = NULL;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      if (!get_user_mods_callbacks[call_number]->is_cache)
        modio::addCallToCache(get_user_mods_callbacks[call_number]->url, response_json);

      mods_size = (u32)response_json["data"].size();
      mods = new ModioMod[mods_size];
      for (u32 i = 0; i < mods_size; i++)
        modioInitMod(&mods[i], response_json["data"][i]);
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  get_user_mods_callbacks[call_number]->callback(get_user_mods_callbacks[call_number]->object, response, NULL, 0);

  delete get_user_mods_callbacks[call_number];
  get_user_mods_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < mods_size; i++)
    modioFreeMod(&mods[i]);
  if (mods)
    delete[] mods;
}

void modioOnGetUserModfiles(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  ModioModfile *modfiles = NULL;
  u32 modfiles_size = 0;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      if (!get_user_modfiles_callbacks[call_number]->is_cache)
        modio::addCallToCache(get_user_modfiles_callbacks[call_number]->url, response_json);

      modfiles_size = (u32)response_json["data"].size();
      modfiles = new ModioModfile[modfiles_size];
      for (u32 i = 0; i < modfiles_size; i++)
        modioInitModfile(&modfiles[i], response_json["data"][i]);
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  get_user_modfiles_callbacks[call_number]->callback(get_user_modfiles_callbacks[call_number]->object, response, modfiles, modfiles_size);

  delete get_user_modfiles_callbacks[call_number];
  get_user_modfiles_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < modfiles_size; i++)
    modioFreeModfile(&modfiles[i]);
  if (modfiles)
    delete[] modfiles;
}

void modioOnGetUserRatings(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  ModioRating *ratings = NULL;
  u32 ratings_size = 0;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      if (!get_user_ratings_callbacks[call_number]->is_cache)
        modio::addCallToCache(get_user_ratings_callbacks[call_number]->url, response_json);

      ratings_size = (u32)response_json["data"].size();
      ratings = new ModioRating[ratings_size];
      for (u32 i = 0; i < ratings_size; i++)
        modioInitRating(&ratings[i], response_json["data"][i]);
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  get_user_ratings_callbacks[call_number]->callback(get_user_ratings_callbacks[call_number]->object, response, ratings, ratings_size);

  delete get_user_ratings_callbacks[call_number];
  get_user_ratings_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < ratings_size; i++)
    modioFreeRating(&ratings[i]);
  if (ratings)
    delete[] ratings;
}

void clearMeCallbackParams()
{
  for (auto get_authenticated_user_callback : get_authenticated_user_callbacks)
    delete get_authenticated_user_callback.second;
  get_authenticated_user_callbacks.clear();

  for (auto get_user_subscriptions_callback : get_user_subscriptions_callbacks)
    delete get_user_subscriptions_callback.second;
  get_user_subscriptions_callbacks.clear();

  for (auto get_user_events_callback : get_user_events_callbacks)
    delete get_user_events_callback.second;
  get_user_events_callbacks.clear();

  for (auto get_user_games_callback : get_user_games_callbacks)
    delete get_user_games_callback.second;
  get_user_games_callbacks.clear();

  for (auto get_user_mods_callback : get_user_mods_callbacks)
    delete get_user_mods_callback.second;
  get_user_mods_callbacks.clear();

  for (auto get_user_modfiles_callback : get_user_modfiles_callbacks)
    delete get_user_modfiles_callback.second;
  get_user_modfiles_callbacks.clear();

  for (auto get_user_ratings_callback : get_user_ratings_callbacks)
    delete get_user_ratings_callback.second;
  get_user_ratings_callbacks.clear();
}
