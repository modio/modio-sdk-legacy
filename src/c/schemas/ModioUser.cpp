#include "c/schemas/ModioUser.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDownload
#include "c/schemas/ModioAvatar.h" // for modioInitAvatar ...

extern "C"
{
  void modioInitUser(ModioUser* user, nlohmann::json user_json)
  {
    user->id = 0;
    if(modio::hasKey(user_json, "id"))
      user->id = user_json["id"];

    user->date_online = 0;
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

  void modioInitUserCpp(ModioUser* modio_user, modio::User* user)
  {
    modio_user->id = user->id;
    modio_user->date_online = user->date_online;

    modio_user->username = new char[user->username.size() + 1];
    strcpy(modio_user->username, user->username.c_str());

    modio_user->name_id = new char[user->name_id.size() + 1];
    strcpy(modio_user->name_id, user->name_id.c_str());

    modio_user->timezone = new char[user->timezone.size() + 1];
    strcpy(modio_user->timezone, user->timezone.c_str());

    modio_user->language = new char[user->language.size() + 1];
    strcpy(modio_user->language, user->language.c_str());

    modio_user->profile_url = new char[user->profile_url.size() + 1];
    strcpy(modio_user->profile_url, user->profile_url.c_str());

    modioInitAvatarCpp(&(modio_user->avatar), &(user->avatar));
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
