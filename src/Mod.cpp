#include "Mod.h"

namespace modworks
{
  Mod* jsonToMod(json mod_json)
  {
    Mod* mod = new Mod;

    mod->name = mod_json["name"];
    mod->id = mod_json["id"];
    mod->game = mod_json["game"];
    mod->logo_url = mod_json["logo"]["full"];
    mod->logo_thumbnail_url = mod_json["logo"]["thumbnail"];
    mod->summary = mod_json["summary"];

    mod->description = "";
    if(mod_json.find("description") != mod_json.end() && !mod_json["description"].is_null())
      mod->description = mod_json["description"];

    if(mod_json.find("modfile") != mod_json.end() && mod_json["modfile"].find("download") != mod_json["modfile"].end())
      mod->download_url = mod_json["modfile"]["download"];

    return mod;
  }
}
