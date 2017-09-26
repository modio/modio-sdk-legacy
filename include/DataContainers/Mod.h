#ifndef MODWORKS_MOD_H
#define MODWORKS_MOD_H

#include <thread>
#include "json/json.hpp"
#include "CurlWrapper.h"
#include "DataContainers/Image.h"
#include "DataContainers/Media.h"
#include "DataContainers/Modfile.h"
#include "DataContainers/Ratings.h"
#include "DataContainers/Tag.h"
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
    int member;
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
