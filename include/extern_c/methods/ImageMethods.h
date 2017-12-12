#ifndef MODIO_IMAGE_METHODS_H
#define MODIO_IMAGE_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "Globals.h"
#include "extern_c/schemas/ModioImage.h"
#include "extern_c/schemas/ModioResponse.h"

extern "C"
{
  void MODIO_DLL modioDownloadImage(void* object, char* image_url, char* path, void (*callback)(void* object, ModioResponse response));
  void MODIO_DLL modioEditModLogo(void* object, int mod_id, char* path, void (*callback)(void* object, ModioResponse response, int mod_id));
}

#endif
