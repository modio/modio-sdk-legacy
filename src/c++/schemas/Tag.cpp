#include "c++/schemas/Tag.h"

namespace modio
{
  void Tag::initialize(ModioTag modio_tag)
  {
    this->date_added = modio_tag.date_added;
    if(modio_tag.name)
      this->name = modio_tag.name;
  }

  nlohmann::json Tag::toJson()
  {
    nlohmann::json tag_json;

    tag_json["date_added"] = this->date_added;
    tag_json["name"] = this->name;

    return tag_json;
  }
}
