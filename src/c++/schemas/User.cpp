#include "c++/schemas/User.h"

namespace modio
{
void User::initialize(ModioUser modio_user)
{
  this->id = modio_user.id;
  this->date_online = modio_user.date_online;
  if (modio_user.username)
    this->username = modio_user.username;
  if (modio_user.name_id)
    this->name_id = modio_user.name_id;
  if (modio_user.timezone)
    this->timezone = modio_user.timezone;
  if (modio_user.language)
    this->language = modio_user.language;
  if (modio_user.profile_url)
    this->profile_url = modio_user.profile_url;
  this->avatar.initialize(modio_user.avatar);
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
