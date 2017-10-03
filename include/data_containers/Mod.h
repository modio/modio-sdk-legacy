#ifndef MODWORKS_MOD_H
#define MODWORKS_MOD_H

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

namespace modworks
{
  class Mod
  {
  public:
    Mod(json mod_json);
    ~Mod();
    int id;
    int game;
    Member* member;
    double price;
    int datereg;
    int dateup;
    Image* logo;
    string homepage;
    string name;
    string nameid;
    string summary;
    string description;
    string metadata;
    Media* media;
    Modfile* modfile;
    Ratings* ratings;
    Tag* tag;
  };
}

#endif