#ifndef MODIO_MOD_H
#define MODIO_MOD_H

#include <thread>
#include "dependencies/json/json.hpp"
#include "wrappers/CurlWrapper.h"
#include "data_containers/Image.h"
#include "data_containers/Member.h"
#include "data_containers/Media.h"
#include "data_containers/Modfile.h"
#include "data_containers/Ratings.h"
#include "data_containers/Tag.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioMod
  {
    int id;
    int game;
    ModioMember* member;
    double price;
    int datereg;
    int dateup;
    ModioImage* logo;
    char* homepage;
    char* name;
    char* nameid;
    char* summary;
    char* description;
    char* metadata;
    ModioMedia* media;
    ModioModfile* modfile;
    ModioRatings* ratings;
    ModioTag* tags_array;
    int tags_array_size;
  };

  void modioInitMod(ModioMod* mod, json mod_json);
  void modioFreeMod(ModioMod* mod);
}

#endif
