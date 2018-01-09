#ifndef MODIO_MOD_H
#define MODIO_MOD_H

#include "c++/schemas/Logo.h"
#include "c++/schemas/User.h"
#include "c++/schemas/Media.h"
#include "c++/schemas/Modfile.h"
#include "c++/schemas/RatingSummary.h"
#include "c++/schemas/Tag.h"
#include "c/schemas/ModioMod.h"
#include "Globals.h"

namespace modio
{
  class Mod
  {
  public:
    u32 id;
    u32 game_id;
    u32 status;
    u32 visible;
    long date_added;
    long date_updated;
    long date_live;
    std::string homepage;
    std::string name;
    std::string name_id;
    std::string summary;
    std::string description;
    std::string metadata_blob;
    std::string profile_url;
    Logo logo;
    User submitted_by;
    Modfile modfile;
    Media media;
    RatingSummary rating_summary;
    std::vector<Tag> tags;

    void initialize(ModioMod mod);
  };
}

#endif
