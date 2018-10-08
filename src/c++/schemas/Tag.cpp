#include "c++/schemas/Tag.h"

namespace modio
{
void Tag::initialize(ModioTag modio_tag)
{
  this->date_added = modio_tag.date_added;
  if (modio_tag.name)
    this->name = modio_tag.name;
}

nlohmann::json toJson(Tag &tag)
{
  nlohmann::json tag_json;

  tag_json["date_added"] = tag.date_added;
  tag_json["name"] = tag.name;

  return tag_json;
}
} // namespace modio
