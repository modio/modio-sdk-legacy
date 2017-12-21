#ifndef MODIO_MODIOFILEHASH_H
#define MODIO_MODIOFILEHASH_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "extern_c/ModioC.h"

using json = nlohmann::json;

extern "C"
{
  void modioInitFilehash(ModioFilehash* filehash, json filehash_json);
  void modioFreeFilehash(ModioFilehash* filehash);
}

#endif
