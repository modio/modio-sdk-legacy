#include "c++/schemas/Game.h"
#include "c/ModioC.h"                      // for ModioGame
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void Game::initialize(ModioGame modio_game)
{
  id = modio_game.id;
  status = modio_game.status;
  maturity_options = modio_game.maturity_options;
  date_added = modio_game.date_added;
  date_updated = modio_game.date_updated;
  presentation_option = modio_game.presentation_option;
  date_live = modio_game.date_live;
  community_options = modio_game.community_options;
  submission_option = modio_game.submission_option;
  curation_option = modio_game.curation_option;
  revenue_options = modio_game.revenue_options;
  api_access_options = modio_game.api_access_options;

  if (modio_game.ugc_name)
    ugc_name = modio_game.ugc_name;
  if (modio_game.instructions_url)
    instructions_url = modio_game.instructions_url;
  if (modio_game.name)
    name = modio_game.name;
  if (modio_game.name_id)
    name_id = modio_game.name_id;
  if (modio_game.summary)
    summary = modio_game.summary;
  if (modio_game.instructions)
    instructions = modio_game.instructions;
  if (modio_game.profile_url)
    profile_url = modio_game.profile_url;

  submitted_by.initialize(modio_game.submitted_by);
  icon.initialize(modio_game.icon);
  logo.initialize(modio_game.logo);
  header.initialize(modio_game.header);

  game_tag_options.resize(modio_game.game_tag_option_array_size);
  for (u32 i = 0; i < modio_game.game_tag_option_array_size; i++)
  {
    game_tag_options[i].initialize(modio_game.game_tag_option_array[i]);
  }
}

nlohmann::json toJson(Game &game)
{
  nlohmann::json game_json;

  game_json["id"] = game.id;
  game_json["status"] = game.status;
  game_json["maturity_options"] = game.maturity_options;
  game_json["date_added"] = game.date_added;
  game_json["date_updated"] = game.date_updated;
  game_json["presentation_option"] = game.presentation_option;
  game_json["date_live"] = game.date_live;
  game_json["community_options"] = game.community_options;
  game_json["submission_option"] = game.submission_option;
  game_json["curation_option"] = game.curation_option;
  game_json["revenue_options"] = game.revenue_options;
  game_json["api_access_options"] = game.api_access_options;
  game_json["ugc_name"] = game.ugc_name;
  game_json["instructions_url"] = game.instructions_url;
  game_json["name"] = game.name;
  game_json["name_id"] = game.name_id;
  game_json["summary"] = game.summary;
  game_json["instructions"] = game.instructions;
  game_json["profile_url"] = game.profile_url;

  game_json["submitted_by"] = modio::toJson(game.submitted_by);
  game_json["icon"] = modio::toJson(game.icon);
  game_json["logo"] = modio::toJson(game.logo);
  game_json["header"] = modio::toJson(game.header);

  nlohmann::json tag_options_json;
  for (auto &game_tag_option : game.game_tag_options)
  {
    tag_options_json.push_back(modio::toJson(game_tag_option));
  }
  game_json["tag_options"] = tag_options_json;

  return game_json;
}
} // namespace modio
