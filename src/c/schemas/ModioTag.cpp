#include "c/schemas/ModioTag.h"

extern "C"
{
  void modioInitTag(ModioTag* tag, nlohmann::json tag_json)
  {
    tag->date_added = 0;
    if(modio::hasKey(tag_json, "date_added"))
      tag->date_added = tag_json["date_added"];

    tag->name = NULL;
    if(modio::hasKey(tag_json, "name"))
    {
      std::string name_str = tag_json["name"];
      tag->name = new char[name_str.size() + 1];
      strcpy(tag->name, name_str.c_str());
    }
  }

  void modioFreeTag(ModioTag* tag)
  {
    if(tag)
    {
      if(tag->name)
        delete[] tag->name;
    }
  }
}
