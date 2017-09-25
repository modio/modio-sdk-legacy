#include "Mod.h"

namespace modworks
{
  Logo jsonToLogo(json logo_json)
  {
    Logo logo;

    if(hasKey(logo_json, "full"))
      logo.full = logo_json["full"];
    if(hasKey(logo_json, "thumbnail"))
      logo.thumbnail = logo_json["thumbnail"];
    if(hasKey(logo_json, "filename"))
      logo.filename = logo_json["filename"];

    return logo;
  }

  Mod* jsonToMod(json mod_json)
  {
    Mod* mod = new Mod;

    if(hasKey(mod_json, "id"))
      mod->id = mod_json["id"];
    if(hasKey(mod_json, "game"))
      mod->game = mod_json["game"];
    if(hasKey(mod_json, "member"))
      mod->member = mod_json["member"];
    if(hasKey(mod_json, "price"))
      mod->price = mod_json["price"];
    if(hasKey(mod_json, "datereg"))
      mod->datereg = mod_json["datereg"];
    if(hasKey(mod_json, "dateup"))
      mod->dateup = mod_json["dateup"];

    if(hasKey(mod_json, "logo"))
      mod->logo = jsonToLogo(mod_json["logo"]);

    if(hasKey(mod_json, "homepage"))
      mod->homepage = mod_json["homepage"];
    if(hasKey(mod_json, "name"))
      mod->name = mod_json["name"];
    if(hasKey(mod_json, "nameid"))
      mod->nameid = mod_json["nameid"];
    if(hasKey(mod_json, "summary"))
      mod->summary = mod_json["summary"];
    if(hasKey(mod_json, "description"))
      mod->description = mod_json["description"];

    //metadata ?
    //media ?

    Modfile modfile;
    Ratings ratings;
    Tag tag;

    if(hasKey(mod_json, "modfile"))
    {
      json modfile_json = mod_json["modfile"];
      if(hasKey(modfile_json, "download"))
      {
        mod->modfile.download = modfile_json["download"];
      }
    }

    return mod;
  }
}
