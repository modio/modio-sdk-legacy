#ifndef MODIO_TAG_METHODS_H
#define MODIO_TAG_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "extern_c/schemas/ModioMod.h"
#include "Globals.h"
#include "extern_c/schemas/ModioResponse.h"

extern "C"
{
  void MODIO_DLL modioGetTags(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size));
  void MODIO_DLL modioAddTags(void* object, int mod_id, char** tags_array, int tags_array_size, void (*callback)(void* object, ModioResponse response, int mod_id));
  void MODIO_DLL modioDeleteTags(void* object, int mod_id, char** tags_array, int tags_array_size, void (*callback)(void* object, ModioResponse response, int mod_id));
}

#endif
