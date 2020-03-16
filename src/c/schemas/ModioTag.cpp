#include "c/schemas/ModioTag.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDownload

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

  void modioInitTagCpp(ModioTag* modio_tag, modio::Tag* tag)
  {
    modio_tag->date_added = tag->date_added;

    modio_tag->name = new char[tag->name.size() + 1];
    strcpy(modio_tag->name, tag->name.c_str());
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
