#ifndef MODIO_MEMBER_H
#define MODIO_MEMBER_H

#include "dependencies/json/json.hpp"
#include "data_containers/Image.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modio
{
  class Member
  {
  public:
    Member(json member_json);
    ~Member();

    int id;
    string username;
    int online;
    Image* avatar;
    string timezone;
    string language;
  };
}

#endif
