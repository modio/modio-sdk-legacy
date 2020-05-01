#include "c/schemas/ModioGameTagOption.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDownload

extern "C"
{
  void modioInitGameTagOption(ModioGameTagOption* game_tag_option, nlohmann::json game_tag_option_json)
  {
    game_tag_option->hidden = 0;
    if(modio::hasKey(game_tag_option_json, "hidden"))
      game_tag_option->hidden = game_tag_option_json["hidden"];

    game_tag_option->name = NULL;
    if(modio::hasKey(game_tag_option_json, "name"))
    {
      std::string name_str = game_tag_option_json["name"];
      game_tag_option->name = new char[name_str.size() + 1];
      strcpy(game_tag_option->name, name_str.c_str());
    }

    game_tag_option->type = NULL;
    if(modio::hasKey(game_tag_option_json, "type"))
    {
      std::string type_str = game_tag_option_json["type"];
      game_tag_option->type = new char[type_str.size() + 1];
      strcpy(game_tag_option->type, type_str.c_str());
    }

    game_tag_option->tags_array = NULL;
    game_tag_option->tags_array_size = 0;
    if(modio::hasKey(game_tag_option_json, "tags"))
    {
      game_tag_option->tags_array_size = (u32)game_tag_option_json["tags"].size();
      game_tag_option->tags_array = new char*[game_tag_option->tags_array_size];
      for(size_t i=0; i<game_tag_option->tags_array_size; i++)
      {
        std::string tag_str = game_tag_option_json["tags"][i];
        game_tag_option->tags_array[i]= new char[tag_str.size() + 1];
        strcpy(game_tag_option->tags_array[i], tag_str.c_str());
      }
    }
  }

  void modioInitGameTagOptionCpp(ModioGameTagOption* modio_game_tag_option, modio::GameTagOption* game_tag_option)
  {
    modio_game_tag_option->hidden = game_tag_option->hidden;

    modio_game_tag_option->name = new char[game_tag_option->name.size() + 1];
    strcpy(modio_game_tag_option->name, game_tag_option->name.c_str());

    modio_game_tag_option->type = new char[game_tag_option->type.size() + 1];
    strcpy(modio_game_tag_option->type, game_tag_option->type.c_str());

    modio_game_tag_option->tags_array_size = (u32)game_tag_option->tags.size();
    modio_game_tag_option->tags_array = new char*[modio_game_tag_option->tags_array_size];
    u32 i = 0;
    for(auto tags_str : game_tag_option->tags)
    {
      strcpy(modio_game_tag_option->tags_array[i], tags_str.c_str());
      i++;
    }
  }

  void modioFreeGameTagOption(ModioGameTagOption* game_tag_option)
  {
    if(game_tag_option)
    {
      if(game_tag_option->name)
        delete[] game_tag_option->name;

      if(game_tag_option->type)
        delete[] game_tag_option->type;

      for(size_t i=0; i<game_tag_option->tags_array_size; i++)
      {
        delete[] game_tag_option->tags_array[i];
      }

      if(game_tag_option->tags_array)
        delete[] game_tag_option->tags_array;
    }
  }
}
