#ifndef MODIO_MODEVENT_H
#define MODIO_MODEVENT_H

#include "Globals.h"
#include "c/schemas/ModioModEvent.h"

namespace modio
{
  class ModEvent
  {
  public:
    u32 id;
    u32 mod_id;
    u32 user_id;
    u32 event_type;
    long date_added;

    void initialize(ModioModEvent mod_event);
    json toJson();
  };
}

#endif
