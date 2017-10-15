#ifndef MODIO_MEMBER_H
#define MODIO_MEMBER_H

#include "dependencies/json/json.hpp"
#include "data_containers/Image.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct Member
  {
    int id;
    string username;
    int online;
    Image* avatar;
    string timezone;
    string language;
  };

  void initMember(Member* member, json member_json);
  void freeMember(Member* member);
}

#endif
