#ifndef MODIO_MOD_H
#define MODIO_MOD_H

#include "instance/schemas/Logo.h"
#include "instance/schemas/User.h"
#include "instance/schemas/Media.h"
#include "instance/schemas/Modfile.h"
#include "instance/schemas/RatingSummary.h"
#include "instance/schemas/Tag.h"
#include "extern_c/schemas/ModioMod.h"
#include "Globals.h"

namespace modio
{
  class Mod
  {
  public:
    u32 id;
    u32 game_id;
    long date_added;
    long date_live;
    long date_updated;
    std::string homepage;
    std::string name;
    std::string name_id;
    std::string summary;
    std::string description;
    std::string metadata_blob;
    std::string profile_url;
    Logo logo;
    User submitted_by;
    Media media;
    Modfile modfile;
    RatingSummary rating_summary;
    std::vector<Tag> tags;

    void initialize(ModioMod mod);
  };
}

#endif
