#ifndef MODIO_MODIOMOD_H
#define MODIO_MODIOMOD_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "extern_c/ModioC.h"
#include "extern_c/schemas/ModioLogo.h"
#include "extern_c/schemas/ModioUser.h"
#include "extern_c/schemas/ModioMedia.h"
#include "extern_c/schemas/ModioModfile.h"
#include "extern_c/schemas/ModioRatingSummary.h"
#include "extern_c/schemas/ModioTag.h"

using json = nlohmann::json;

extern "C"
{
  void modioInitMod(ModioMod* mod, json mod_json);
  void modioFreeMod(ModioMod* mod);
}

#endif
