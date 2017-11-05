#ifndef MODIO_TAG_METHODS_H
#define MODIO_TAG_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"

extern "C"
{
  void MODIO_DLL modioGetTags(ModioMod* mod, void (*callback)(ModioResponse* response, ModioTag* tags_array, int tags_array_size));
  void MODIO_DLL modioAddTags(ModioMod* mod, char** tags_array, int tags_array_size, void (*callback)(ModioResponse* response, ModioTag* tags_array, int tags_array_size));
  void MODIO_DLL modioDeleteTags(ModioMod* mod, char** tags_array, int tags_array_size, void (*callback)(ModioResponse* response, ModioTag* tags_array, int tags_array_size));
}

#endif
