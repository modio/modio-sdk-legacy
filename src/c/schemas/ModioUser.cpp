#include "c/schemas/ModioUser.h"

extern "C"
{
  void modioInitUser(ModioUser* user, nlohmann::json user_json)
  {
    user->id = 0;
    if(modio::hasKey(user_json, "id"))
      user->id = user_json["id"];

    user->date_online = -1;
    if(modio::hasKey(user_json, "date_online"))
      user->date_online = user_json["date_online"];

    user->username = NULL;
    if(modio::hasKey(user_json, "username"))
    {
      std::string username_str = user_json["username"];
      user->username = new char[username_str.size() + 1];
      strcpy(user->username, username_str.c_str());
    }

    user->name_id = NULL;
    if(modio::hasKey(user_json, "name_id"))
    {
      std::string name_id_str = user_json["name_id"];
      user->name_id = new char[name_id_str.size() + 1];
      strcpy(user->name_id, name_id_str.c_str());
    }

    user->timezone = NULL;
    if(modio::hasKey(user_json, "timezone"))
    {
      std::string timezone_str = user_json["timezone"];
      user->timezone = new char[timezone_str.size() + 1];
      strcpy(user->timezone, timezone_str.c_str());
    }

    user->language = NULL;
    if(modio::hasKey(user_json, "language"))
    {
      std::string language_str = user_json["language"];
      user->language = new char[language_str.size() + 1];
      strcpy(user->language, language_str.c_str());
    }

    user->profile_url = NULL;
    if(modio::hasKey(user_json, "profile_url"))
    {
      std::string profile_url_str = user_json["profile_url"];
      user->profile_url = new char[profile_url_str.size() + 1];
      strcpy(user->profile_url, profile_url_str.c_str());
    }

    nlohmann::json avatar_json;
    if(modio::hasKey(user_json, "avatar"))
      avatar_json = user_json["avatar"];
    modioInitAvatar(&(user->avatar), avatar_json);
  }

  void modioFreeUser(ModioUser* user)
  {
    if(user)
    {
      if(user->username)
        delete[] user->username;
      if(user->name_id)
        delete[] user->name_id;
      if(user->timezone)
        delete[] user->timezone;
      if(user->language)
        delete[] user->language;
      if(user->profile_url)
        delete[] user->profile_url;

      modioFreeAvatar(&(user->avatar));
    }
  }
}
