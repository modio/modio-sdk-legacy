#include "Mod.h"

Mod::Mod(json mod_json)
{
  this->id = mod_json["id"];
  this->game = mod_json["game"];
  this->logo_url = mod_json["logo"]["full"];
  this->logo_thumbnail_url = mod_json["logo"]["thumbnail"];
  this->name = mod_json["name"];
  this->summary = mod_json["summary"];
  this->description = mod_json["description"];
}
