#ifndef MODIO_MODIOFILEHASH_H
#define MODIO_MODIOFILEHASH_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioFilehash
  {
    char* md5;
  };

  void modioInitFilehash(ModioFilehash* filehash, json filehash_json);
  void modioFreeFilehash(ModioFilehash* filehash);
}

#endif
