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

    mod->submitted_by = NULL;
    if(modio::hasKey(mod_json, "submitted_by"))
    {
      mod->submitted_by = new ModioUser;
      modioInitUser(mod->submitted_by, mod_json["submitted_by"]);
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
      modioInitImage(mod->logo, mod_json["logo"]);
    }

    mod->homepage = NULL;
    if(modio::hasKey(mod_json, "homepage"))
    {
      string homepage_str = mod_json["homepage"];
      mod->homepage = new char[homepage_str.size() + 1];
      strcpy(mod->homepage, homepage_str.c_str());
    }

    mod->name = NULL;
    if(modio::hasKey(mod_json, "name"))
    {
      string name_str = mod_json["name"];
      mod->name = new char[name_str.size() + 1];
      strcpy(mod->name, name_str.c_str());
    }

    mod->nameid = NULL;
    if(modio::hasKey(mod_json, "nameid"))
    {
      string nameid_str = mod_json["nameid"];
      mod->nameid = new char[nameid_str.size() + 1];
      strcpy(mod->nameid, nameid_str.c_str());
    }

    mod->summary = NULL;
    if(modio::hasKey(mod_json, "summary"))
    {
      string summary_str = mod_json["summary"];
      mod->summary = new char[summary_str.size() + 1];
      strcpy(mod->summary, summary_str.c_str());
    }

    mod->description = NULL;
    if(modio::hasKey(mod_json, "description"))
    {
      string description_str = mod_json["description"];
      mod->description = new char[description_str.size() + 1];
      strcpy(mod->description, description_str.c_str());
    }

    mod->metadata = NULL;
    if(modio::hasKey(mod_json, "metadata"))
    {
      string metadata_str = mod_json["metadata"];
      mod->metadata = new char[metadata_str.size() + 1];
      strcpy(mod->metadata, metadata_str.c_str());
    }

    mod->media = NULL;
    if(modio::hasKey(mod_json, "media"))
    {
      mod->media = new ModioMedia;
      modioInitMedia(mod->media, mod_json["media"]);
    }

    mod->modfile = NULL;
    if(modio::hasKey(mod_json, "modfile"))
    {
      mod->modfile = new ModioModfile;
      modioInitModfile(mod->modfile, mod_json["modfile"]);
    }

    mod->ratings = NULL;
    if(modio::hasKey(mod_json, "ratings"))
    {
      mod->ratings = new ModioRatings;
      modioInitRatings(mod->ratings, mod_json["ratings"]);
    }

    mod->tags_array = NULL;
    mod->tags_array_size = 0;
    if(modio::hasKey(mod_json, "tags"))
    {
      mod->tags_array_size = mod_json["tags"].size();
      mod->tags_array = new ModioTag[mod->tags_array_size];
      for(int i=0; i<mod->tags_array_size; i++)
      {
        modioInitTag(&(mod->tags_array[i]), mod_json["tags"][i]);
      }
    }
  }

  void modioFreeMod(ModioMod* mod)
  {
    if(mod->logo)
      modioFreeImage(mod->logo);
    if(mod->media)
      modioFreeMedia(mod->media);
    if(mod->modfile)
      modioFreeModfile(mod->modfile);
    if(mod->ratings)
      modioFreeRatings(mod->ratings);
    for(int i=0;i<mod->tags_array_size; i++)
      modioFreeTag(&(mod->tags_array[i]));
  }
}
