#include "DataContainers/Mod.h"

namespace modworks
{
  Mod::Mod(json mod_json)
  {
    this->id = -1;
    if(hasKey(mod_json, "id"))
      this->id = mod_json["id"];

    this->game = -1;
    if(hasKey(mod_json, "game"))
      this->game = mod_json["game"];

    this->member = -1;
    if(hasKey(mod_json, "member"))
      this->member = mod_json["member"];

    this->price = -1;
    if(hasKey(mod_json, "price"))
      this->price = mod_json["price"];

    this->datereg = -1;
    if(hasKey(mod_json, "datereg"))
      this->datereg = mod_json["datereg"];

    this->dateup = -1;
    if(hasKey(mod_json, "dateup"))
      this->dateup = mod_json["dateup"];

    this->logo = NULL;
    if(hasKey(mod_json, "logo"))
      this->logo = new Image(mod_json["logo"]);

    this->homepage = "";
    if(hasKey(mod_json, "homepage"))
      this->homepage = mod_json["homepage"];

    this->name = "";
    if(hasKey(mod_json, "name"))
      this->name = mod_json["name"];

    this->nameid = "";
    if(hasKey(mod_json, "nameid"))
      this->nameid = mod_json["nameid"];

    this->summary = "";
    if(hasKey(mod_json, "summary"))
      this->summary = mod_json["summary"];

    this->description = "";
    if(hasKey(mod_json, "description"))
      this->description = mod_json["description"];

    this->metadata = "";
    if(hasKey(mod_json, "metadata"))
      this->metadata = mod_json["metadata"];

    this->media = NULL;
    if(hasKey(mod_json, "media"))
      this->media = new Media(mod_json["media"]);

    this->modfile = NULL;
    if(hasKey(mod_json, "modfile"))
      this->modfile = new Modfile(mod_json["modfile"]);

    this->ratings = NULL;
    if(hasKey(mod_json, "ratings"))
      this->ratings = new Ratings(mod_json["ratings"]);

    this->tag = NULL;
    if(hasKey(mod_json, "tag"))
      this->tag = new Tag(mod_json["tag"]);
  }

  Mod::~Mod()
  {
    delete logo;
    delete media;
    delete modfile;
    delete ratings;
    delete tag;
  }
}
