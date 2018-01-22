#include "c/schemas/ModioModEvent.h"

extern "C"
{
  void modioInitModEvent(ModioModEvent* mod_event, json mod_event_json)
  {
    mod_event->id = 0;
    if(modio::hasKey(mod_event_json, "id"))
      mod_event->id = mod_event_json["id"];

    mod_event->mod_id = 0;
    if(modio::hasKey(mod_event_json, "mod_id"))
      mod_event->mod_id = mod_event_json["mod_id"];

    mod_event->user_id = 0;
    if(modio::hasKey(mod_event_json, "user_id"))
      mod_event->user_id = mod_event_json["user_id"];

    mod_event->event_type = 0;
    if(modio::hasKey(mod_event_json, "event_type"))
      mod_event->event_type = mod_event_json["event_type"];

    mod_event->date_added = 0;
    if(modio::hasKey(mod_event_json, "date_added"))
      mod_event->date_added = mod_event_json["date_added"];
  }

  void modioFreeModEvent(ModioModEvent* tag)
  {
    //No pointers
  }
}
