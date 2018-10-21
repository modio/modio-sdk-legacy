#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GetAuthenticatedUserCall *> get_authenticated_user_calls;
std::map<u32, GetUserSubscriptionsCall *> get_user_subscriptions_calls;
std::map<u32, GetUserEventsCall *> get_user_events_calls;
std::map<u32, GetUserGamesCall *> get_user_games_calls;
std::map<u32, GetUserModsCall *> get_user_mods_calls;
std::map<u32, GetUserModfilesCall *> get_user_modfiles_calls;
std::map<u32, GetUserRatingsCall *> get_user_ratings_calls;

void onGetAuthenticatedUser(void *object, ModioResponse modio_response, ModioUser modio_user)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  modio::User user;

  if (modio_response.code == 200)
  {
    user.initialize(modio_user);
  }

  get_authenticated_user_calls[call_id]->callback((const Response &)response, user);

  delete (u32 *)object;
  delete get_authenticated_user_calls[call_id];
  get_authenticated_user_calls.erase(call_id);
}

void onGetUserSubscriptions(void *object, ModioResponse modio_response, ModioMod mods[], u32 mods_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Mod> mods_vector;
  mods_vector.resize(mods_size);
  for (u32 i = 0; i < mods_size; i++)
  {
    mods_vector[i].initialize(mods[i]);
  }

  get_user_subscriptions_calls[call_id]->callback((const Response &)response, mods_vector);

  delete (u32 *)object;
  delete get_user_subscriptions_calls[call_id];
  get_user_subscriptions_calls.erase(call_id);
}

void onGetUserEvents(void *object, ModioResponse modio_response, ModioEvent *events_array, u32 events_array_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Event> event_vector;
  event_vector.resize(events_array_size);
  for (u32 i = 0; i < events_array_size; i++)
  {
    event_vector[i].initialize(events_array[i]);
  }
  get_user_events_calls[call_id]->callback((const Response &)response, event_vector);

  delete get_user_events_calls[call_id];
  delete (u32 *)object;
  get_user_events_calls.erase(call_id);
}

void onGetUserGames(void *object, ModioResponse modio_response, ModioGame games[], u32 games_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Game> games_vector;
  games_vector.resize(games_size);
  for (u32 i = 0; i < games_size; i++)
  {
    games_vector[i].initialize(games[i]);
  }

  get_user_games_calls[call_id]->callback((const Response &)response, games_vector);

  delete (u32 *)object;
  delete get_user_games_calls[call_id];
  get_user_games_calls.erase(call_id);
}

void onGetUserMods(void *object, ModioResponse modio_response, ModioMod mods[], u32 mods_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Mod> mods_vector;
  mods_vector.resize(mods_size);
  for (u32 i = 0; i < mods_size; i++)
  {
    mods_vector[i].initialize(mods[i]);
  }

  get_user_mods_calls[call_id]->callback((const Response &)response, mods_vector);

  delete (u32 *)object;
  delete get_user_mods_calls[call_id];
  get_user_mods_calls.erase(call_id);
}

void onGetUserModfiles(void *object, ModioResponse modio_response, ModioModfile modfiles[], u32 modfiles_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Modfile> modfiles_vector;
  modfiles_vector.resize(modfiles_size);
  for (u32 i = 0; i < modfiles_size; i++)
  {
    modfiles_vector[i].initialize(modfiles[i]);
  }

  get_user_modfiles_calls[call_id]->callback((const Response &)response, modfiles_vector);

  delete (u32 *)object;
  delete get_user_modfiles_calls[call_id];
  get_user_modfiles_calls.erase(call_id);
}

void onGetUserRatings(void *object, ModioResponse modio_response, ModioRating ratings[], u32 ratings_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Rating> ratings_vector;
  ratings_vector.resize(ratings_size);
  for (u32 i = 0; i < ratings_size; i++)
  {
    ratings_vector[i].initialize(ratings[i]);
  }

  get_user_ratings_calls[call_id]->callback((const Response &)response, ratings_vector);

  delete (u32 *)object;
  delete get_user_ratings_calls[call_id];
  get_user_ratings_calls.erase(call_id);
}

void clearMeRequestCalls()
{
  for(auto get_authenticated_user_call : get_authenticated_user_calls)
    delete get_authenticated_user_call.second;
  get_authenticated_user_calls.clear();

  for(auto get_user_subscriptions_call : get_user_subscriptions_calls)
    delete get_user_subscriptions_call.second;
  get_user_subscriptions_calls.clear();

  for(auto get_user_events_call : get_user_events_calls)
    delete get_user_events_call.second;
  get_user_events_calls.clear();

  for(auto get_user_games_call : get_user_games_calls)
    delete get_user_games_call.second;
  get_user_games_calls.clear();

  for(auto get_user_mods_call : get_user_mods_calls)
    delete get_user_mods_call.second;
  get_user_mods_calls.clear();

  for(auto get_user_modfiles_call : get_user_modfiles_calls)
    delete get_user_modfiles_call.second;
  get_user_modfiles_calls.clear();

  for(auto get_user_ratings_call : get_user_ratings_calls)
    delete get_user_ratings_call.second;
  get_user_ratings_calls.clear();
}
} // namespace modio
