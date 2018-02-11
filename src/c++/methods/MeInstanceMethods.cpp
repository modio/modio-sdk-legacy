#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::getAuthenticatedUser(const std::function<void(const modio::Response& response, const modio::User& user)>& callback)
  {
    const struct GetAuthenticatedUserCall* get_authenticated_user_call = new GetAuthenticatedUserCall{callback};
    get_authenticated_user_calls[this->current_call_id] = (GetAuthenticatedUserCall*)get_authenticated_user_call;

    modioGetAuthenticatedUser((void*)new u32(this->current_call_id), &onGetAuthenticatedUser);

    this->current_call_id++;
  }

  void Instance::getUserSubscriptions(modio::FilterCreator& filter, const std::function<void(const modio::Response& response, const std::vector<modio::Mod> & mods)>& callback)
  {
    const struct GetUserSubscriptionsCall* get_user_subscriptions_call = new GetUserSubscriptionsCall{callback};
    get_user_subscriptions_calls[this->current_call_id] = (GetUserSubscriptionsCall*)get_user_subscriptions_call;

    modioGetUserSubscriptions((void*)new u32(this->current_call_id), *filter.getFilter(), &onGetUserSubscriptions);

    this->current_call_id++;
  }

  void Instance::getUserGames(modio::FilterCreator& filter, const std::function<void(const modio::Response& response, const std::vector<modio::Game> & games)>& callback)
  {
    const struct GetUserGamesCall* get_user_games_call = new GetUserGamesCall{callback};
    get_user_games_calls[this->current_call_id] = (GetUserGamesCall*)get_user_games_call;

    modioGetUserGames((void*)new u32(this->current_call_id), *filter.getFilter(), &onGetUserGames);

    this->current_call_id++;
  }

  void Instance::getUserMods(modio::FilterCreator& filter, const std::function<void(const modio::Response& response, const std::vector<modio::Mod> & mods)>& callback)
  {
    const struct GetUserModsCall* get_user_mods_call = new GetUserModsCall{callback};
    get_user_mods_calls[this->current_call_id] = (GetUserModsCall*)get_user_mods_call;

    modioGetUserMods((void*)new u32(this->current_call_id), *filter.getFilter(), &onGetUserMods);

    this->current_call_id++;
  }

  void Instance::getUserModfiles(modio::FilterCreator& filter, const std::function<void(const modio::Response& response, const std::vector<modio::Modfile> & modfiles)>& callback)
  {
    const struct GetUserModfilesCall* get_user_modfiles_call = new GetUserModfilesCall{callback};
    get_user_modfiles_calls[this->current_call_id] = (GetUserModfilesCall*)get_user_modfiles_call;

    modioGetUserModfiles((void*)new u32(this->current_call_id), *filter.getFilter(), &onGetUserModfiles);

    this->current_call_id++;
  }
}
