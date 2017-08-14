#ifndef MOD_H
#define MOD_H

#include <iostream>
#include <thread>
#include "json/json.hpp"
#include "CurlWrapper.h"

using namespace std;
using json = nlohmann::json;

class Mod
{
public:
  int id;
  int game;
  string logo_url;
  string logo_thumbnail_url;
  string name;
  string summary;
  string description;

  string logo_thumbnail_path;

  Mod(json mod_json);
  void downloadLogoThumbnail(function< void(int, Mod*) > callback);
};

#endif
