#include "Utility.h"
#include "Globals.h"
#include "c/ModioC.h"
#include "c++/schemas/Mod.h"

namespace modio
{
  void onModfileChangedEvent(void* object, ModioResponse response);
  void onModUpdateEvent(void* object, ModioResponse response, ModioMod modio_mod);
  void onGetAllModEventsPoll(void* object, ModioResponse response, ModioModEvent* mod_events_array, u32 mod_events_array_size);
  void pollEvents();
}
