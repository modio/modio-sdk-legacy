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

  Modfile jsonToModfile(json modfile_json)
  {
    Modfile modfile;
    if(hasKey(modfile_json, "id"))
      modfile.id = modfile_json["id"];
    if(hasKey(modfile_json, "mod"))
      modfile.mod = modfile_json["mod"];
    if(hasKey(modfile_json, "member"))
      modfile.member = modfile_json["member"];
    if(hasKey(modfile_json, "datevirus"))
      modfile.datevirus = modfile_json["datevirus"];
    if(hasKey(modfile_json, "virusstatus"))
      modfile.virusstatus = modfile_json["virusstatus"];
    if(hasKey(modfile_json, "viruspoitive"))
      modfile.viruspoitive = modfile_json["viruspoitive"];
    if(hasKey(modfile_json, "filesize"))
      modfile.filesize = modfile_json["filesize"];
    if(hasKey(modfile_json, "filehash"))
      modfile.filehash = modfile_json["filehash"];
    if(hasKey(modfile_json, "filename"))
      modfile.filename = modfile_json["filename"];
    if(hasKey(modfile_json, "version"))
      modfile.version = modfile_json["version"];
    //virustotal ?
    if(hasKey(modfile_json, "changelog"))
      modfile.changelog = modfile_json["changelog"];
    if(hasKey(modfile_json, "download"))
      modfile.download = modfile_json["download"];

    return modfile;
  }

  Ratings jsonToRatings(json ratings_json)
  {
    Ratings ratings;

    if(hasKey(ratings_json, "total"))
      ratings.total = ratings_json["total"];
    if(hasKey(ratings_json, "positive"))
      ratings.positive = ratings_json["positive"];
    if(hasKey(ratings_json, "negative"))
      ratings.negative = ratings_json["negative"];
    if(hasKey(ratings_json, "weighted"))
      ratings.weighted = ratings_json["weighted"];
    if(hasKey(ratings_json, "percentage"))
      ratings.percentage = ratings_json["percentage"];
    if(hasKey(ratings_json, "stars"))
      ratings.stars = ratings_json["stars"];
    if(hasKey(ratings_json, "text"))
      ratings.text = ratings_json["text"];

    return ratings;
  }

  Tag jsonToTag(json tag_json)
  {
    Tag tag;

    if(hasKey(tag_json, "game"))
      tag.game = tag_json["game"];
    if(hasKey(tag_json, "mod"))
      tag.mod = tag_json["mod"];
    if(hasKey(tag_json, "date"))
      tag.date = tag_json["date"];
    if(hasKey(tag_json, "member"))
      tag.member = tag_json["member"];
    if(hasKey(tag_json, "tag"))
      tag.tag = tag_json["tag"];

    return tag;
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

    mod->modfile = jsonToModfile(mod_json["modfile"]);
    mod->ratings = jsonToRatings(mod_json["ratings"]);
    mod->tag = jsonToTag(mod_json["tag"]);

    return mod;
  }
}
