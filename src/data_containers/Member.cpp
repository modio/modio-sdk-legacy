#include "data_containers/Member.h"

extern "C"
{
  void modioInitMember(ModioMember* member, json member_json)
  {
    member->id = -1;
    if(modio::hasKey(member_json, "id"))
    {
      member->id = member_json["id"];
    }

    member->username = NULL;
    if(modio::hasKey(member_json, "username"))
    {
      string username_str = member_json["username"];
      member->username = new char[username_str.size() + 1];
      strcpy(member->username, username_str.c_str());
    }

    member->online = -1;
    if(modio::hasKey(member_json, "online"))
    {
      member->online = member_json["online"];
    }

    member->avatar = NULL;
    if(modio::hasKey(member_json, "avatar"))
    {
      member->avatar = new ModioImage;
      modioInitImage(member->avatar, member_json["avatar"]);
    }

    member->timezone = NULL;
    if(modio::hasKey(member_json, "timezone"))
    {
      string timezone_str = member_json["timezone"];
      member->timezone = new char[timezone_str.size() + 1];
      strcpy(member->timezone, timezone_str.c_str());
    }

    member->language = NULL;
    if(modio::hasKey(member_json, "language"))
    {
      string language_str = member_json["language"];
      member->language = new char[language_str.size() + 1];
      strcpy(member->language, language_str.c_str());
    }
  }

  void modioFreeMember(ModioMember* member)
  {
    if(member->avatar)
      modioFreeImage(member->avatar);
  }
}
