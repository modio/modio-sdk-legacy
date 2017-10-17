#include "data_containers/Mod.h"

extern "C"
{
  void initMod(Mod* mod, json mod_json)
  {
    mod->id = -1;
    if(modio::hasKey(mod_json, "id"))
      mod->id = mod_json["id"];

    mod->game = -1;
    if(modio::hasKey(mod_json, "game"))
      mod->game = mod_json["game"];

    mod->member = NULL;
    if(modio::hasKey(mod_json, "member"))
    {
      mod->member = new Member;
      initMember(mod->member, mod_json["member"]);
    }

    mod->price = -1;
    if(modio::hasKey(mod_json, "price"))
      mod->price = mod_json["price"];

    mod->datereg = -1;
    if(modio::hasKey(mod_json, "datereg"))
      mod->datereg = mod_json["datereg"];

    mod->dateup = -1;
    if(modio::hasKey(mod_json, "dateup"))
      mod->dateup = mod_json["dateup"];

    mod->logo = NULL;
    if(modio::hasKey(mod_json, "logo"))
    {
      mod->logo = new Image;
      initImage(mod->logo, mod_json["logo"]);
    }

    mod->homepage = "";
    if(modio::hasKey(mod_json, "homepage"))
      mod->homepage = mod_json["homepage"];

    mod->name = "";
    if(modio::hasKey(mod_json, "name"))
      mod->name = mod_json["name"];

    mod->nameid = "";
    if(modio::hasKey(mod_json, "nameid"))
      mod->nameid = mod_json["nameid"];

    mod->summary = "";
    if(modio::hasKey(mod_json, "summary"))
      mod->summary = mod_json["summary"];

    mod->description = "";
    if(modio::hasKey(mod_json, "description"))
      mod->description = mod_json["description"];

    mod->metadata = "";
    if(modio::hasKey(mod_json, "metadata"))
      mod->metadata = mod_json["metadata"];

    mod->media = NULL;
    if(modio::hasKey(mod_json, "media"))
    {
      mod->media = new Media;
      initMedia(mod->media, mod_json["media"]);
    }

    mod->modfile = NULL;
    if(modio::hasKey(mod_json, "modfile"))
    {
      mod->modfile = new Modfile;
      initModfile(mod->modfile, mod_json["modfile"]);
    }

    mod->ratings = NULL;
    if(modio::hasKey(mod_json, "ratings"))
    {
      mod->ratings = new Ratings;
      initRatings(mod->ratings, mod_json["ratings"]);
    }

    mod->tag = NULL;
    if(modio::hasKey(mod_json, "tag"))
    {
      mod->tag = new Tag;
      initTag(mod->tag, mod_json["tag"]);
    }
  }

  void freeMod(Mod* mod)
  {
    if(mod->logo)
      freeImage(mod->logo);
    if(mod->media)
      freeMedia(mod->media);
    if(mod->modfile)
      freeModfile(mod->modfile);
    if(mod->ratings)
      freeRatings(mod->ratings);
    if(mod->tag)
      freeTag(mod->tag);
  }
}
