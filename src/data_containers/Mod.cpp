#include "data_containers/Mod.h"

extern "C"
{
  void modioInitMod(ModioMod* mod, json mod_json)
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
      mod->member = new ModioMember;
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
      mod->logo = new ModioImage;
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
      mod->media = new ModioMedia;
      initMedia(mod->media, mod_json["media"]);
    }

    mod->modfile = NULL;
    if(modio::hasKey(mod_json, "modfile"))
    {
      mod->modfile = new ModioModfile;
      initModfile(mod->modfile, mod_json["modfile"]);
    }

    mod->ratings = NULL;
    if(modio::hasKey(mod_json, "ratings"))
    {
      mod->ratings = new ModioRatings;
      initRatings(mod->ratings, mod_json["ratings"]);
    }

    mod->tag = NULL;
    if(modio::hasKey(mod_json, "tag"))
    {
      mod->tag = new ModioTag;
      initTag(mod->tag, mod_json["tag"]);
    }
  }

  void modioFreeMod(ModioMod* mod)
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
