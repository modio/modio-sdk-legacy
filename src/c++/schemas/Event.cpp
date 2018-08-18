#include "c++/schemas/Event.h"

namespace modio
{
  void Event::initialize(ModioEvent modio_event)
  {
    this->id = modio_event.id;
    this->mod_id = modio_event.mod_id;
    this->user_id = modio_event.user_id;
    this->event_type = modio_event.event_type;
    this->date_added = modio_event.date_added;
  }

  nlohmann::json Event::toJson()
  {
    nlohmann::json event_json;

    event_json["id"] = this->id;
    event_json["mod_id"] = this->mod_id;
    event_json["user_id"] = this->user_id;
    event_json["event_type"] = this->event_type;
    event_json["date_added"] = this->date_added;

    return event_json;
  }
}
