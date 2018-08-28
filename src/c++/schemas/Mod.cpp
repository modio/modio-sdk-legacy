#include "c++/schemas/Mod.h"

namespace modio
{
  void Mod::initialize(ModioMod modio_mod)
  {
    this->id = modio_mod.id;
    this->game_id = modio_mod.game_id;
    this->status = modio_mod.status;
    this->visible = modio_mod.visible;
    this->maturity_option = modio_mod.maturity_option;
    this->date_added = modio_mod.date_added;
    this->date_updated = modio_mod.date_updated;
    this->date_live = modio_mod.date_live;
    if(modio_mod.homepage_url)
      this->homepage_url = modio_mod.homepage_url;
    if(modio_mod.name)
      this->name = modio_mod.name;
    if(modio_mod.name_id)
      this->name_id = modio_mod.name_id;
    if(modio_mod.summary)
      this->summary = modio_mod.summary;
    if(modio_mod.description)
      this->description = modio_mod.description;
    if(modio_mod.description_plaintext)
      this->description_plaintext = modio_mod.description_plaintext;
    if(modio_mod.metadata_blob)
      this->metadata_blob = modio_mod.metadata_blob;
    if(modio_mod.profile_url)
      this->profile_url = modio_mod.profile_url;
    this->logo.initialize(modio_mod.logo);
    this->submitted_by.initialize(modio_mod.submitted_by);
    this->modfile.initialize(modio_mod.modfile);
    this->media.initialize(modio_mod.media);
    this->stats.initialize(modio_mod.stats);
    this->tags.resize(modio_mod.tags_array_size);
    for(u32 i = 0; i < modio_mod.tags_array_size; i++)
    {
      this->tags[i].initialize(modio_mod.tags_array[i]);
    }
    this->metadata_kvps.resize(modio_mod.metadata_kvp_array_size);
    for(u32 i = 0; i < modio_mod.metadata_kvp_array_size; i++)
    {
      this->metadata_kvps[i].initialize(modio_mod.metadata_kvp_array[i]);
    }
  }

  nlohmann::json Mod::toJson()
  {
    nlohmann::json mod_json;

    mod_json["id"] = this->id;
    mod_json["game_id"] = this->game_id;
    mod_json["status"] = this->status;
    mod_json["visible"] = this->visible;
    mod_json["maturity_option"] = this->maturity_option;
    mod_json["date_added"] = this->date_added;
    mod_json["date_updated"] = this->date_updated;
    mod_json["date_live"] = this->date_live;
    mod_json["homepage_url"] = this->homepage_url;
    mod_json["name"] = this->name;
    mod_json["name_id"] = this->name_id;
    mod_json["summary"] = this->summary;
    mod_json["description"] = this->description;
    mod_json["description_plaintext"] = this->description_plaintext;
    mod_json["metadata_blob"] = this->metadata_blob;
    mod_json["profile_url"] = this->profile_url;
    mod_json["logo"] = this->logo.toJson();
    mod_json["submitted_by"] = this->submitted_by.toJson();
    mod_json["modfile"] = this->modfile.toJson();
    mod_json["media"] = this->media.toJson();
    mod_json["stats"] = this->stats.toJson();

    nlohmann::json tags_json;
    for(auto& tag : tags)
    {
      tags_json.push_back(tag.toJson());
    }
    mod_json["tags"] = tags_json;

    nlohmann::json metadata_kvps_json;
    for(auto& metadata_kvp : metadata_kvps)
    {
      metadata_kvps_json.push_back(metadata_kvp.toJson());
    }
    mod_json["metadata_kvp"] = metadata_kvps_json;

    return mod_json;
  }
}
