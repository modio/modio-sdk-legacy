#include "c++/schemas/Game.h"

namespace modio
{
void Game::initialize(ModioGame modio_game)
{
  this->id = modio_game.id;
  this->status = modio_game.status;
  this->maturity_options = modio_game.maturity_options;
  this->date_added = modio_game.date_added;
  this->date_updated = modio_game.date_updated;
  this->presentation_option = modio_game.presentation_option;
  this->date_live = modio_game.date_live;
  this->community_options = modio_game.community_options;
  this->submission_option = modio_game.submission_option;
  this->curation_option = modio_game.curation_option;
  this->revenue_options = modio_game.revenue_options;
  this->api_access_options = modio_game.api_access_options;

  if (modio_game.ugc_name)
    this->ugc_name = modio_game.ugc_name;
  if (modio_game.instructions_url)
    this->instructions_url = modio_game.instructions_url;
  if (modio_game.name)
    this->name = modio_game.name;
  if (modio_game.name_id)
    this->name_id = modio_game.name_id;
  if (modio_game.summary)
    this->summary = modio_game.summary;
  if (modio_game.instructions)
    this->instructions = modio_game.instructions;
  if (modio_game.profile_url)
    this->profile_url = modio_game.profile_url;

  this->submitted_by.initialize(modio_game.submitted_by);
  this->icon.initialize(modio_game.icon);
  this->logo.initialize(modio_game.logo);
  this->header.initialize(modio_game.header);

  this->game_tag_options.resize(modio_game.game_tag_option_array_size);
  for (u32 i = 0; i < modio_game.game_tag_option_array_size; i++)
  {
    this->game_tag_options[i].initialize(modio_game.game_tag_option_array[i]);
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
