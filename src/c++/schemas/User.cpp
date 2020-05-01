#include "c++/schemas/User.h"
#include "c/ModioC.h"                      // for ModioUser
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void User::initialize(ModioUser modio_user)
{
  id = modio_user.id;
  date_online = modio_user.date_online;
  if (modio_user.username)
    username = modio_user.username;
  if (modio_user.name_id)
    name_id = modio_user.name_id;
  if (modio_user.timezone)
    timezone = modio_user.timezone;
  if (modio_user.language)
    language = modio_user.language;
  if (modio_user.profile_url)
    profile_url = modio_user.profile_url;
  avatar.initialize(modio_user.avatar);
}

nlohmann::json toJson(User &user)
{
  nlohmann::json user_json;

  user_json["id"] = user.id;
  user_json["date_online"] = user.date_online;
  user_json["username"] = user.username;
  user_json["name_id"] = user.name_id;
  user_json["timezone"] = user.timezone;
  user_json["language"] = user.language;
  user_json["profile_url"] = user.profile_url;
  user_json["avatar"] = modio::toJson(user.avatar);

  return user_json;
}
} // namespace modio
