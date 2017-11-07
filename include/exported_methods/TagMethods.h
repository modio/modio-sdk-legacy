#ifndef MODIO_TAG_METHODS_H
#define MODIO_TAG_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"

extern "C"
{
  void MODIO_DLL modioGetTags(int mod_id, void (*callback)(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size));
  void MODIO_DLL modioAddTags(int mod_id, char** tags_array, int tags_array_size, void (*callback)(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size));
  void MODIO_DLL modioDeleteTags(int mod_id, char** tags_array, int tags_array_size, void (*callback)(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size));
}

#endif
