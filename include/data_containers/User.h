#ifndef MODIO_USER_H
#define MODIO_USER_H

#include "dependencies/json/json.hpp"
#include "data_containers/Image.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioUser
  {
    int id;
    char* username;
    int online;
    ModioImage* avatar;
    char* timezone;
    char* language;
  };

  void modioInitUser(ModioUser* user, json user_json);
  void modioFreeUser(ModioUser* user);
}

#endif
