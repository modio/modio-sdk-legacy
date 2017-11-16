#include "data_containers/User.h"

extern "C"
{
  void modioInitUser(ModioUser* user, json user_json)
  {
    user->id = -1;
    if(modio::hasKey(user_json, "id"))
    {
      user->id = user_json["id"];
    }

    user->username = NULL;
    if(modio::hasKey(user_json, "username"))
    {
      string username_str = user_json["username"];
      user->username = new char[username_str.size() + 1];
      strcpy(user->username, username_str.c_str());
    }

    user->online = -1;
    if(modio::hasKey(user_json, "online"))
    {
      user->online = user_json["online"];
    }

    user->avatar = NULL;
    if(modio::hasKey(user_json, "avatar"))
    {
      user->avatar = new ModioImage;
      modioInitImage(user->avatar, user_json["avatar"]);
    }

    user->timezone = NULL;
    if(modio::hasKey(user_json, "timezone"))
    {
      string timezone_str = user_json["timezone"];
      user->timezone = new char[timezone_str.size() + 1];
      strcpy(user->timezone, timezone_str.c_str());
    }

    user->language = NULL;
    if(modio::hasKey(user_json, "language"))
    {
      string language_str = user_json["language"];
      user->language = new char[language_str.size() + 1];
      strcpy(user->language, language_str.c_str());
    }
  }

  void modioFreeUser(ModioUser* user)
  {
    if(user->avatar)
      modioFreeImage(user->avatar);
  }
}
