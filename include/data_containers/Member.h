#ifndef MODIO_MEMBER_H
#define MODIO_MEMBER_H

#include "dependencies/json/json.hpp"
#include "data_containers/Image.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioMember
  {
    int id;
    char* username;
    int online;
    ModioImage* avatar;
    char* timezone;
    char* language;
  };

  void initMember(ModioMember* member, json member_json);
  void freeMember(ModioMember* member);
}

#endif
