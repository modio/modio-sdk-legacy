#include "c++/schemas/Mod.h"
#include "c/ModioC.h"                      // for ModioMod
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void Mod::initialize(ModioMod modio_mod)
{
  id = modio_mod.id;
  game_id = modio_mod.game_id;
  status = modio_mod.status;
  visible = modio_mod.visible;
  maturity_option = modio_mod.maturity_option;
  date_added = modio_mod.date_added;
  date_updated = modio_mod.date_updated;
  date_live = modio_mod.date_live;
  if (modio_mod.homepage_url)
    homepage_url = modio_mod.homepage_url;
  if (modio_mod.name)
    name = modio_mod.name;
  if (modio_mod.name_id)
    name_id = modio_mod.name_id;
  if (modio_mod.summary)
    summary = modio_mod.summary;
  if (modio_mod.description)
    description = modio_mod.description;
  if (modio_mod.description_plaintext)
    description_plaintext = modio_mod.description_plaintext;
  if (modio_mod.metadata_blob)
    metadata_blob = modio_mod.metadata_blob;
  if (modio_mod.profile_url)
    profile_url = modio_mod.profile_url;
  logo.initialize(modio_mod.logo);
  submitted_by.initialize(modio_mod.submitted_by);
  modfile.initialize(modio_mod.modfile);
  media.initialize(modio_mod.media);
  stats.initialize(modio_mod.stats);
  tags.resize(modio_mod.tags_array_size);
  u32 i = 0;
  for(auto& tag : tags)
  {
    tag.initialize(modio_mod.tags_array[i++]);
  }
  i = 0;
  metadata_kvps.resize(modio_mod.metadata_kvp_array_size);
  for (auto& metadata_kvp : metadata_kvps)
  {
    metadata_kvp.initialize(modio_mod.metadata_kvp_array[i++]);
  }
}

nlohmann::json toJson(Mod &mod)
{
  nlohmann::json mod_json;

  mod_json["id"] = mod.id;
  mod_json["game_id"] = mod.game_id;
  mod_json["status"] = mod.status;
  mod_json["visible"] = mod.visible;
  mod_json["maturity_option"] = mod.maturity_option;
  mod_json["date_added"] = mod.date_added;
  mod_json["date_updated"] = mod.date_updated;
  mod_json["date_live"] = mod.date_live;
  mod_json["homepage_url"] = mod.homepage_url;
  mod_json["name"] = mod.name;
  mod_json["name_id"] = mod.name_id;
  mod_json["summary"] = mod.summary;
  mod_json["description"] = mod.description;
  mod_json["description_plaintext"] = mod.description_plaintext;
  mod_json["metadata_blob"] = mod.metadata_blob;
  mod_json["profile_url"] = mod.profile_url;
  mod_json["logo"] = modio::toJson(mod.logo);
  mod_json["submitted_by"] = modio::toJson(mod.submitted_by);
  mod_json["modfile"] = modio::toJson(mod.modfile);
  mod_json["media"] = modio::toJson(mod.media);
  mod_json["stats"] = modio::toJson(mod.stats);

  nlohmann::json tags_json;
  for (auto &tag : mod.tags)
  {
    tags_json.push_back(modio::toJson(tag));
  }
  mod_json["tags"] = tags_json;

  nlohmann::json metadata_kvps_json;
  for (auto &metadata_kvp : mod.metadata_kvps)
  {
    metadata_kvps_json.push_back(modio::toJson(metadata_kvp));
  }
  mod_json["metadata_kvp"] = metadata_kvps_json;

  return mod_json;
}
} // namespace modio
