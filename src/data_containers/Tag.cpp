#include "data_containers/Tag.h"

extern "C"
{
  void modioInitTag(ModioTag* tag, json tag_json)
  {
    tag->game = -1;
    if(modio::hasKey(tag_json, "game"))
      tag->game = tag_json["game"];

    tag->mod = -1;
    if(modio::hasKey(tag_json, "mod"))
      tag->mod = tag_json["mod"];

    tag->date = -1;
    if(modio::hasKey(tag_json, "date"))
      tag->date = tag_json["date"];

    tag->tag = NULL;
    if(modio::hasKey(tag_json, "tag"))
    {
      string tag_str = tag_json["tag"];
      tag->tag = new char[tag_str.size() + 1];
      strcpy(tag->tag, tag_str.c_str());
    }
  }

  void modioFreeTag(ModioTag* tag)
  {
    delete tag;
  }
}
