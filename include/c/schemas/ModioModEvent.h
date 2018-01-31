#ifndef MODIO_MODIOMODEVENT_H
#define MODIO_MODIOMODEVENT_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "c/ModioC.h"

using json = nlohmann::json;

extern "C"
{
  void modioInitModEvent(ModioModEvent* mod_event, json mod_event_json);
  void modioFreeModEvent(ModioModEvent* mod_event);
}

#endif
