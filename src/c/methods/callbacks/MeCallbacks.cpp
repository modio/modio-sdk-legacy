#include "c/methods/callbacks/MeCallbacks.h"

std::map< u32, GetAuthenticatedUserParams* > get_authenticated_user_callbacks;
std::map< u32, GetUserSubscriptionsParams* > get_user_subscriptions_callbacks;
std::map< u32, GetUserEventsParams* > get_user_events_callbacks;
std::map< u32, GetUserGamesParams* > get_user_games_callbacks;
std::map< u32, GetUserModsParams* > get_user_mods_callbacks;
std::map< u32, GetUserModfilesParams* > get_user_modfiles_callbacks;

void modioOnGetAuthenticatedUser(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioUser user;
  modioInitUser(&user, response_json);

  get_authenticated_user_callbacks[call_number]->callback(get_authenticated_user_callbacks[call_number]->object, response, user);

  delete get_authenticated_user_callbacks[call_number];
  get_authenticated_user_callbacks.erase(call_number);
  modioFreeResponse(&response);
}

void modioOnGetUserSubscriptions(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  if(response.code == 200)
  {
    if(!get_user_subscriptions_callbacks[call_number]->is_cache)
      modio::addCallToCache(get_user_subscriptions_callbacks[call_number]->url, response_json);

    u32 mods_size = (u32)response_json["data"].size();
    ModioMod* mods = new ModioMod[mods_size];
    for(u32 i=0; i<mods_size; i++)
    {
      modioInitMod(&mods[i], response_json["data"][i]);
    }
    get_user_subscriptions_callbacks[call_number]->callback(get_user_subscriptions_callbacks[call_number]->object, response, mods, mods_size);
    for(u32 i=0; i<mods_size; i++)
    {
      modioFreeMod(&mods[i]);
    }
    delete[] mods;
  }else
  {
    get_user_subscriptions_callbacks[call_number]->callback(get_user_subscriptions_callbacks[call_number]->object, response, NULL, 0);
  }
  delete get_user_subscriptions_callbacks[call_number];
  get_user_subscriptions_callbacks.erase(call_number);
  modioFreeResponse(&response);
}

void modioOnGetUserEvents(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioEvent* events_array = NULL;
  u32 events_array_size = 0;
  if(response.code == 200)
  {
    try
    {
      if(modio::hasKey(response_json, "data"))
      {
        events_array_size = (u32)response_json["data"].size();
        events_array = new ModioEvent[events_array_size];

        for(u32 i=0; i<events_array_size; i++)
        {
          modioInitEvent(&(events_array[i]), response_json["data"][i]);
        }
      }
    }catch(nlohmann::json::parse_error &e)
    {
      modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
    }
  }
  get_user_events_callbacks[call_number]->callback(get_user_events_callbacks[call_number]->object, response, events_array, events_array_size);

  for(u32 i=0; i<events_array_size; i++)
  {
    modioFreeEvent(&(events_array[i]));
  }

  if(events_array)
    delete[] events_array;
  delete get_user_events_callbacks[call_number];
  get_user_events_callbacks.erase(call_number);
}

void modioOnGetUserGames(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  if(response.code == 200)
  {
    if(!get_user_games_callbacks[call_number]->is_cache)
      modio::addCallToCache(get_user_games_callbacks[call_number]->url, response_json);

    u32 games_size = (u32)response_json["data"].size();
    ModioGame* games = new ModioGame[games_size];
    for(u32 i=0; i<games_size; i++)
    {
      modioInitGame(&games[i], response_json["data"][i]);
    }
    get_user_games_callbacks[call_number]->callback(get_user_games_callbacks[call_number]->object, response, games, games_size);
    for(u32 i=0; i<games_size; i++)
    {
      modioFreeGame(&games[i]);
    }
    delete[] games;
  }else
  {
    get_user_games_callbacks[call_number]->callback(get_user_games_callbacks[call_number]->object, response, NULL, 0);
  }
  delete get_user_games_callbacks[call_number];
  get_user_games_callbacks.erase(call_number);
  modioFreeResponse(&response);
}

void modioOnGetUserMods(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  if(response.code == 200)
  {
    if(!get_user_mods_callbacks[call_number]->is_cache)
      modio::addCallToCache(get_user_mods_callbacks[call_number]->url, response_json);

    u32 mods_size = (u32)response_json["data"].size();
    ModioMod* mods = new ModioMod[mods_size];
    for(u32 i=0; i<mods_size; i++)
    {
      modioInitMod(&mods[i], response_json["data"][i]);
    }
    get_user_mods_callbacks[call_number]->callback(get_user_mods_callbacks[call_number]->object, response, mods, mods_size);
    for(u32 i=0; i<mods_size; i++)
    {
      modioFreeMod(&mods[i]);
    }
    delete[] mods;
  }else
  {
    get_user_mods_callbacks[call_number]->callback(get_user_mods_callbacks[call_number]->object, response, NULL, 0);
  }
  delete get_user_mods_callbacks[call_number];
  get_user_mods_callbacks.erase(call_number);
  modioFreeResponse(&response);
}

void modioOnGetUserModfiles(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  if(response.code == 200)
  {
    if(!get_user_modfiles_callbacks[call_number]->is_cache)
      modio::addCallToCache(get_user_modfiles_callbacks[call_number]->url, response_json);

    u32 modfiles_size = (u32)response_json["data"].size();
    ModioModfile* modfiles = new ModioModfile[modfiles_size];
    for(u32 i=0; i<modfiles_size; i++)
    {
      modioInitModfile(&modfiles[i], response_json["data"][i]);
    }
    get_user_modfiles_callbacks[call_number]->callback(get_user_modfiles_callbacks[call_number]->object, response, modfiles, modfiles_size);
    for(u32 i=0; i<modfiles_size; i++)
    {
      modioFreeModfile(&modfiles[i]);
    }
    delete[] modfiles;
  }else
  {
    get_user_modfiles_callbacks[call_number]->callback(get_user_modfiles_callbacks[call_number]->object, response, NULL, 0);
  }
  delete get_user_modfiles_callbacks[call_number];
  get_user_modfiles_callbacks.erase(call_number);
  modioFreeResponse(&response);
}
