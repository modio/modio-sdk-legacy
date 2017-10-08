#include "data_containers/Member.h"

namespace modio
{
  Member::Member(json member_json)
  {
    this->id = -1;
    if(hasKey(member_json, "id"))
      this->id = member_json["id"];

    this->username = "";
    if(hasKey(member_json, "username"))
      this->username = member_json["username"];

    this->online = -1;
    if(hasKey(member_json, "online"))
      this->online = member_json["online"];

    this->avatar = NULL;
    if(hasKey(member_json, "avatar"))
      this->avatar = new Image(member_json["avatar"]);

    this->timezone = "";
    if(hasKey(member_json, "timezone"))
      this->timezone = member_json["timezone"];

    this->language = "";
    if(hasKey(member_json, "language"))
      this->language = member_json["language"];
  }

  Member::~Member()
  {
    if(avatar)
      delete avatar;
  }
}
