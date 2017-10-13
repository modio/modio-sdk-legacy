#include "data_containers/Tag.h"

namespace modio
{
  void initTag(Tag* tag, json tag_json)
  {
    tag->game = -1;
    if(hasKey(tag_json, "game"))
      tag->game = tag_json["game"];

    tag->mod = -1;
    if(hasKey(tag_json, "mod"))
      tag->mod = tag_json["mod"];

    tag->date = -1;
    if(hasKey(tag_json, "date"))
      tag->date = tag_json["date"];

    tag->tag = "";
    if(hasKey(tag_json, "tag"))
      tag->tag = tag_json["tag"];
  }

  void freeTag(Tag* tag)
  {
    delete tag;
  }
}
