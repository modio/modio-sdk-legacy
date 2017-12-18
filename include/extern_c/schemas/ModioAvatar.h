#ifndef MODIO_MODIOAVATAR_H
#define MODIO_MODIOAVATAR_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioAvatar
  {
    char* filename;
    char* original;
    char* thumb_50x50;
    char* thumb_100x100;
  };

  void modioInitAvatar(ModioAvatar* avatar, json avatar_json);
  void modioFreeAvatar(ModioAvatar* avatar);
}

#endif
