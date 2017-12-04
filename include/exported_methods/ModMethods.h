#ifndef MODIO_MOD_METHODS_H
#define MODIO_MOD_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/ModioMod.h"
#include "handlers/ModioModHandler.h"
#include "Globals.h"
#include "handlers/ModioFilterHandler.h"
#include "data_containers/ModioResponse.h"

extern "C"
{
  void MODIO_DLL modioGetMods(void* object, ModioFilterHandler* filter, void (*callback)(void* object, ModioResponse response, ModioMod* mods, int mods_size));
  void MODIO_DLL modioAddMod(void* object, ModioModHandler* mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod* mod));
  void MODIO_DLL modioEditMod(void* object, int mod_id, ModioModHandler* mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod* mod));
  void MODIO_DLL modioDeleteMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id));
  void MODIO_DLL modioSetUserModVote(void* object, int mod_id, bool vote_up, void (*callback)(void* object, ModioResponse response, int mod_id));
  void MODIO_DLL modioSubscribeMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id));
  void MODIO_DLL modioUnsubscribeMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id));
}

#endif
