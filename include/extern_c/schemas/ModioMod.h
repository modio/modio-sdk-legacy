#ifndef MODIO_MODIOMOD_H
#define MODIO_MODIOMOD_H

#include <thread>
#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "wrappers/CurlWrapper.h"
#include "extern_c/schemas/ModioLogo.h"
#include "extern_c/schemas/ModioUser.h"
#include "extern_c/schemas/ModioMedia.h"
#include "extern_c/schemas/ModioModfile.h"
#include "extern_c/schemas/ModioRatingSummary.h"
#include "extern_c/schemas/ModioTag.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioMod
  {
    u32 id;
    u32 game_id;
    long date_added;
    long date_live;
    long date_updated;
    char* homepage;
    char* name;
    char* name_id;
    char* summary;
    char* description;
    char* metadata_blob;
    char* profile_url;
    ModioLogo logo;
    ModioUser submitted_by;
    ModioMedia media;
    ModioModfile modfile;
    ModioRatingSummary rating_summary;
    ModioTag* tags_array;
    u32 tags_array_size;
  };

  void modioInitMod(ModioMod* mod, json mod_json);
  void modioFreeMod(ModioMod* mod);
}

#endif
