#ifndef MODIO_MODIOMOD_H
#define MODIO_MODIOMOD_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "c/ModioC.h"
#include "c/schemas/ModioLogo.h"
#include "c/schemas/ModioUser.h"
#include "c/schemas/ModioMedia.h"
#include "c/schemas/ModioModfile.h"
#include "c/schemas/ModioRatingSummary.h"
#include "c/schemas/ModioTag.h"

using json = nlohmann::json;

extern "C"
{
  void modioInitMod(ModioMod* mod, json mod_json);
  void modioFreeMod(ModioMod* mod);
}

#endif
