#include "c++/schemas/ModEvent.h"

namespace modio
{
  void ModEvent::initialize(ModioModEvent modio_mod_event)
  {
    this->id = modio_mod_event.id;
    this->mod_id = modio_mod_event.mod_id;
    this->user_id = modio_mod_event.user_id;
    this->event_type = modio_mod_event.event_type;
    this->date_added = modio_mod_event.date_added;
  }

  json ModEvent::toJson()
  {
    json mod_event_json;

    mod_event_json["id"] = this->id;
    mod_event_json["mod_id"] = this->mod_id;
    mod_event_json["user_id"] = this->user_id;
    mod_event_json["event_type"] = this->event_type;
    mod_event_json["date_added"] = this->date_added;

    return mod_event_json;
  }
}
