#include "data_containers/ModioTag.h"

extern "C"
{
  void modioInitTag(ModioTag* tag, json tag_json)
  {
    tag->date_added = -1;
    if(modio::hasKey(tag_json, "date_added"))
      tag->date_added = tag_json["date_added"];

    tag->tag = NULL;
    if(modio::hasKey(tag_json, "tag"))
    {
      std::string tag_str = tag_json["tag"];
      tag->tag = new char[tag_str.size() + 1];
      strcpy(tag->tag, tag_str.c_str());
    }
  }

  void modioFreeTag(ModioTag* tag)
  {
    if(tag)
      delete[] tag;
  }
}
