#include "c/schemas/ModioUserEvent.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDownload

extern "C"
{
  void modioInitUserEvent(ModioUserEvent* event, nlohmann::json event_json)
  {
    event->id = 0;
    if(modio::hasKey(event_json, "id"))
      event->id = event_json["id"];

    event->game_id = 0;
    if(modio::hasKey(event_json, "game_id"))
      event->game_id = event_json["game_id"];

    event->mod_id = 0;
    if(modio::hasKey(event_json, "mod_id"))
      event->mod_id = event_json["mod_id"];

    event->user_id = 0;
    if(modio::hasKey(event_json, "user_id"))
      event->user_id = event_json["user_id"];

    event->event_type = 0;
    if(modio::hasKey(event_json, "event_type"))
    {
      if(event_json["event_type"] == "MODFILE_CHANGED")
        event->event_type = MODIO_EVENT_MODFILE_CHANGED;
      else if(event_json["event_type"] == "MOD_AVAILABLE")
        event->event_type = MODIO_EVENT_MOD_AVAILABLE;
      else if(event_json["event_type"] == "MOD_UNAVAILABLE")
        event->event_type = MODIO_EVENT_MOD_UNAVAILABLE;
      else if(event_json["event_type"] == "MOD_EDITED")
        event->event_type = MODIO_EVENT_MOD_EDITED;
      else if(event_json["event_type"] == "MOD_DELETED")
        event->event_type = MODIO_EVENT_MOD_DELETED;
      else if(event_json["event_type"] == "USER_TEAM_JOIN")
        event->event_type = MODIO_EVENT_USER_TEAM_JOIN;
      else if(event_json["event_type"] == "USER_TEAM_LEAVE")
        event->event_type = MODIO_EVENT_USER_TEAM_LEAVE;
      else if(event_json["event_type"] == "USER_SUBSCRIBE")
        event->event_type = MODIO_EVENT_USER_SUBSCRIBE;
      else if(event_json["event_type"] == "USER_UNSUBSCRIBE")
        event->event_type = MODIO_EVENT_USER_UNSUBSCRIBE;
      else
        event->event_type = MODIO_EVENT_UNDEFINED;
    }

    event->date_added = 0;
    if(modio::hasKey(event_json, "date_added"))
      event->date_added = event_json["date_added"];
  }

  void modioInitUserEventCpp(ModioUserEvent* modio_user_event, modio::UserEvent* user_event)
  {
    modio_user_event->id = user_event->id;
    modio_user_event->game_id = user_event->game_id;
    modio_user_event->mod_id = user_event->mod_id;
    modio_user_event->user_id = user_event->user_id;
    modio_user_event->event_type = user_event->event_type;
    modio_user_event->date_added = user_event->date_added;
  }

  void modioFreeUserEvent(ModioUserEvent* tag)
  {
    //No pointers
  }
}
