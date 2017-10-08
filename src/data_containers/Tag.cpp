#include "data_containers/Tag.h"

namespace modio
{
  Tag::Tag(json tag_json)
  {
    this->game = -1;
    if(hasKey(tag_json, "game"))
      this->game = tag_json["game"];

    this->mod = -1;
    if(hasKey(tag_json, "mod"))
      this->mod = tag_json["mod"];

    this->date = -1;
    if(hasKey(tag_json, "date"))
      this->date = tag_json["date"];

    this->tag = "";
    if(hasKey(tag_json, "tag"))
      this->tag = tag_json["tag"];
  }
}
