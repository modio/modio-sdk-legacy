#include "c++/ModIOInstance.h"
#include "ModioUtility.h"
#include "c++/methods/callbacks/MeInstanceCallbacks.h"
#include "c++/creators/FilterCreator.h"

namespace modio
{
void Instance::getAuthenticatedUser(const std::function<void(const modio::Response &response, const modio::User &user)> &callback)
{
  struct GetAuthenticatedUserCall *get_authenticated_user_call = new GetAuthenticatedUserCall{callback};
  get_authenticated_user_calls[current_call_id] = get_authenticated_user_call;

  modioGetAuthenticatedUser((void*)((uintptr_t)current_call_id), &onGetAuthenticatedUser);

  current_call_id++;
}

void Instance::getUserSubscriptions(modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Mod> &mods)> &callback)
{
  struct GetUserSubscriptionsCall *get_user_subscriptions_call = new GetUserSubscriptionsCall{callback};
  get_user_subscriptions_calls[current_call_id] = get_user_subscriptions_call;

  modioGetUserSubscriptions((void*)((uintptr_t)current_call_id), *filter.getFilter(), &onGetUserSubscriptions);

  current_call_id++;
}

void Instance::getUserEvents(modio::FilterCreator &filter, const std::function<void(const modio::Response &, const std::vector<modio::UserEvent> &events)> &callback)
{
  struct GetUserEventsCall *get_user_events_call = new GetUserEventsCall{callback};
  get_user_events_calls[current_call_id] = get_user_events_call;

  modioGetUserEvents((void*)((uintptr_t)current_call_id), *filter.getFilter(), &onGetUserEvents);

  current_call_id++;
}

void Instance::getUserGames(modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Game> &games)> &callback)
{
  struct GetUserGamesCall *get_user_games_call = new GetUserGamesCall{callback};
  get_user_games_calls[current_call_id] = get_user_games_call;

  modioGetUserGames((void*)((uintptr_t)current_call_id), *filter.getFilter(), &onGetUserGames);

  current_call_id++;
}

void Instance::getUserMods(modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Mod> &mods)> &callback)
{
  struct GetUserModsCall *get_user_mods_call = new GetUserModsCall{callback};
  get_user_mods_calls[current_call_id] = get_user_mods_call;

  modioGetUserMods((void*)((uintptr_t)current_call_id), *filter.getFilter(), &onGetUserMods);

  current_call_id++;
}

void Instance::getUserModfiles(modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Modfile> &modfiles)> &callback)
{
  struct GetUserModfilesCall *get_user_modfiles_call = new GetUserModfilesCall{callback};
  get_user_modfiles_calls[current_call_id] = get_user_modfiles_call;

  modioGetUserModfiles((void*)((uintptr_t)current_call_id), *filter.getFilter(), &onGetUserModfiles);

  current_call_id++;
}

void Instance::getUserRatings(modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Rating> &ratings)> &callback)
{
  struct GetUserRatingsCall *get_user_ratings_call = new GetUserRatingsCall{callback};
  get_user_ratings_calls[current_call_id] = get_user_ratings_call;

  modioGetUserRatings((void*)((uintptr_t)current_call_id), *filter.getFilter(), &onGetUserRatings);

  current_call_id++;
}
} // namespace modio
