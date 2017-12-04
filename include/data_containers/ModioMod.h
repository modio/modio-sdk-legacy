#ifndef MODIO_MODIOMOD_H
#define MODIO_MODIOMOD_H

#include <thread>
#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "wrappers/CurlWrapper.h"
#include "data_containers/ModioImage.h"
#include "data_containers/ModioUser.h"
#include "data_containers/ModioMedia.h"
#include "data_containers/ModioModfile.h"
#include "data_containers/ModioRatings.h"
#include "data_containers/ModioTag.h"

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
    ModioImage logo;
    ModioUser submitted_by;
    ModioMedia media;
    ModioModfile modfile;
    ModioRatings ratings;
    ModioTag* tags_array;
    int tags_array_size;
  };

  void modioInitMod(ModioMod* mod, json mod_json);
  void modioFreeMod(ModioMod* mod);
}

#endif
