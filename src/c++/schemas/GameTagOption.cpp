#include "c++/schemas/GameTagOption.h"

namespace modio
{
  void GameTagOption::initialize(ModioGameTagOption modio_game_tag_option)
  {
    this->hidden = modio_game_tag_option.hidden;

    if(modio_game_tag_option.name)
      this->name = modio_game_tag_option.name;
    if(modio_game_tag_option.type)
      this->type = modio_game_tag_option.type;

    this->tags.resize(modio_game_tag_option.tags_array_size);
    for(u32 i = 0; i < modio_game_tag_option.tags_array_size; i++)
    {
      this->tags[i] = modio_game_tag_option.tags_array[i];
    }
  }

  nlohmann::json GameTagOption::toJson()
  {
    nlohmann::json game_tag_option_json;

    game_tag_option_json["hidden"] = this->hidden;
    game_tag_option_json["name"] = this->name;
    game_tag_option_json["type"] = this->type;

    nlohmann::json tags_json;
    for(auto& tag : tags)
    {
      tags_json.push_back(tag);
    }
    game_tag_option_json["tags"] = tags_json;

    return game_tag_option_json;
  }
}
