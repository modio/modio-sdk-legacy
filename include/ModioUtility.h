#ifndef MODIO_MODIOUTILITY_H
#define MODIO_MODIOUTILITY_H

#include "Utility.h"
#include "Globals.h"
#include "c/ModioC.h"
#include "c++/schemas/Mod.h"

namespace modio
{
  void onModsUpdateEvent(void *object, ModioResponse response, ModioMod *mods, u32 mods_size);
  void onGetAllEventsPoll(void* object, ModioResponse response, ModioEvent* events_array, u32 events_array_size);
  void pollEvents();
}

#endif