#include "data_containers/Member.h"

extern "C"
{
  void initMember(Member* member, json member_json)
  {
    member->id = -1;
    if(modio::hasKey(member_json, "id"))
      member->id = member_json["id"];

    member->username = "";
    if(modio::hasKey(member_json, "username"))
      member->username = member_json["username"];

    member->online = -1;
    if(modio::hasKey(member_json, "online"))
      member->online = member_json["online"];

    member->avatar = NULL;
    if(modio::hasKey(member_json, "avatar"))
    {
      member->avatar = new Image;
      initImage(member->avatar, member_json["avatar"]);
    }

    member->timezone = "";
    if(modio::hasKey(member_json, "timezone"))
      member->timezone = member_json["timezone"];

    member->language = "";
    if(modio::hasKey(member_json, "language"))
      member->language = member_json["language"];
  }

  void freeMember(Member* member)
  {
    if(member->avatar)
      freeImage(member->avatar);
  }
}
