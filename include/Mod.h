#ifndef MODWORKS_MOD_H
#define MODWORKS_MOD_H

#include <thread>
#include "json/json.hpp"
#include "CurlWrapper.h"

using namespace std;
using json = nlohmann::json;

namespace modworks
{
  struct Mod
  {
    //Required
    int id;
    int game;
    string name;
    string homepage;
    string summary;

    //Not required
    double price;
    int stock;
    string description;
    string metadata;
    string nameid;
    int modfile;

    //Urls
    string logo_url;
    string logo_thumbnail_url;
    string download_url;
  };

  Mod* jsonToMod(json mod_json);
}

#endif
