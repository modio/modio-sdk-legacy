#ifndef MOD_H
#define MOD_H

#include <json/json.hpp>
#include <iostream>

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

  Mod(json mod_json);
};

#endif
