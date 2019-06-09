#include "c++/schemas/ModEvent.h"

namespace modio
{
void ModEvent::initialize(ModioModEvent modio_event)
{
  id = modio_event.id;
  mod_id = modio_event.mod_id;
  user_id = modio_event.user_id;
  event_type = modio_event.event_type;
  date_added = modio_event.date_added;
}

nlohmann::json toJson(ModEvent &event)
{
  nlohmann::json event_json;

  event_json["id"] = event.id;
  event_json["mod_id"] = event.mod_id;
  event_json["user_id"] = event.user_id;
  event_json["event_type"] = event.event_type;
  event_json["date_added"] = event.date_added;

  return event_json;
}
} // namespace modio
