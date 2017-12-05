#include "extern_c/schemas/ModioMod.h"

extern "C"
{
  void modioInitMod(ModioMod* mod, json mod_json)
  {
    mod->id = 0;
    if(modio::hasKey(mod_json, "id"))
      mod->id = mod_json["id"];

    mod->game_id = 0;
    if(modio::hasKey(mod_json, "game_id"))
      mod->game_id = mod_json["game_id"];

    mod->date_added = -1;
    if(modio::hasKey(mod_json, "date_added"))
      mod->date_added = mod_json["date_added"];

    mod->date_live = -1;
    if(modio::hasKey(mod_json, "date_live"))
      mod->date_live = mod_json["date_live"];

    mod->date_updated = -1;
    if(modio::hasKey(mod_json, "date_updated"))
      mod->date_updated = mod_json["date_updated"];

    mod->homepage = NULL;
    if(modio::hasKey(mod_json, "homepage"))
    {
      std::string homepage_str = mod_json["homepage"];
      mod->homepage = new char[homepage_str.size() + 1];
      strcpy(mod->homepage, homepage_str.c_str());
    }

    mod->name = NULL;
    if(modio::hasKey(mod_json, "name"))
    {
      std::string name_str = mod_json["name"];
      mod->name = new char[name_str.size() + 1];
      strcpy(mod->name, name_str.c_str());
    }

    mod->name_id = NULL;
    if(modio::hasKey(mod_json, "name_id"))
    {
      std::string name_id_str = mod_json["name_id"];
      mod->name_id = new char[name_id_str.size() + 1];
      strcpy(mod->name_id, name_id_str.c_str());
    }

    mod->summary = NULL;
    if(modio::hasKey(mod_json, "summary"))
    {
      std::string summary_str = mod_json["summary"];
      mod->summary = new char[summary_str.size() + 1];
      strcpy(mod->summary, summary_str.c_str());
    }

    mod->description = NULL;
    if(modio::hasKey(mod_json, "description"))
    {
      std::string description_str = mod_json["description"];
      mod->description = new char[description_str.size() + 1];
      strcpy(mod->description, description_str.c_str());
    }

    mod->metadata_blob = NULL;
    if(modio::hasKey(mod_json, "metadata_blob"))
    {
      std::string metadata_blob_str = mod_json["metadata_blob"];
      mod->metadata_blob = new char[metadata_blob_str.size() + 1];
      strcpy(mod->metadata_blob, metadata_blob_str.c_str());
    }

    mod->profile_url = NULL;
    if(modio::hasKey(mod_json, "profile_url"))
    {
      std::string profile_url_str = mod_json["profile_url"];
      mod->profile_url = new char[profile_url_str.size() + 1];
      strcpy(mod->profile_url, profile_url_str.c_str());
    }

    if(modio::hasKey(mod_json, "logo"))
    {
      modioInitImage(&(mod->logo), mod_json["logo"]);
    }

    if(modio::hasKey(mod_json, "submitted_by"))
    {
      modioInitUser(&(mod->submitted_by), mod_json["submitted_by"]);
    }

    if(modio::hasKey(mod_json, "media"))
    {
      modioInitMedia(&(mod->media), mod_json["media"]);
    }

    if(modio::hasKey(mod_json, "modfile"))
    {
      modioInitModfile(&(mod->modfile), mod_json["modfile"]);
    }

    if(modio::hasKey(mod_json, "rating_summary"))
    {
      modioInitRatingSummary(&(mod->rating_summary), mod_json["rating_summary"]);
    }

    mod->tags_array = NULL;
    mod->tags_array_size = 0;
    if(modio::hasKey(mod_json, "tags"))
    {
      mod->tags_array_size = mod_json["tags"].size();
      mod->tags_array = new ModioTag[mod->tags_array_size];
      for(u32 i=0; i<mod->tags_array_size; i++)
      {
        modioInitTag(&(mod->tags_array[i]), mod_json["tags"][i]);
      }
    }
  }

  void modioFreeMod(ModioMod* mod)
  {
    for(u32 i=0;i<mod->tags_array_size; i++)
      modioFreeTag(&(mod->tags_array[i]));
  }
}
