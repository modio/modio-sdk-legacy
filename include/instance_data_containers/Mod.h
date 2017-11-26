#ifndef MODIO_MOD_H
#define MODIO_MOD_H

#include "data_containers/ModioMod.h"
#include "Globals.h"
#include "instance_data_containers/Image.h"
#include "instance_data_containers/User.h"
#include "instance_data_containers/Media.h"
#include "instance_data_containers/Modfile.h"
#include "instance_data_containers/Ratings.h"
#include "instance_data_containers/Tag.h"

namespace modio
{
  class Mod
  {
  public:
    u32 id;
    u32 game_id;
    double price;
    long date_added;
    long date_live;
    long date_updated;
    std::string homepage;
    std::string name;
    std::string name_id;
    std::string summary;
    std::string description;
    std::string metadata_blob;
    std::string url;
    Image logo;
    User submitted_by;
    Media media;
    Modfile modfile;
    Ratings ratings;
    std::vector<Tag> tags;

    void initialize(ModioMod mod);
  };
}

#endif
