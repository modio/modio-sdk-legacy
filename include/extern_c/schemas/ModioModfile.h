#ifndef MODIO_MODIOMODFILE_H
#define MODIO_MODIOMODFILE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "extern_c/ModioC.h"
#include "extern_c/schemas/ModioFilehash.h"

using json = nlohmann::json;

extern "C"
{
  void modioInitModfile(ModioModfile* modfile, json modfile_json);
  void modioFreeModfile(ModioModfile* modfile);
}

#endif
