#ifndef MODIO_IMAGE_METHODS_H
#define MODIO_IMAGE_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Image.h"
#include "Globals.h"
#include "Filter.h"

extern "C"
{
  void MODIO_DLL modioDownloadImage(char* image_url, char* path, void (*callback)(ModioResponse* response, char* path));
  void MODIO_DLL modioEditModLogo(int mod_id, char* path, void (*callback)(ModioResponse* response, int mod_id));
}

#endif
