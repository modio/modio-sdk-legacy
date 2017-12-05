#ifndef MODIO_MODFILE_METHODS_H
#define MODIO_MODFILE_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "extern_c/handlers/ModioModfileHandler.h"
#include "Globals.h"
#include "extern_c/schemas/ModioMod.h"
#include "extern_c/schemas/ModioResponse.h"

extern "C"
{
  void MODIO_DLL modioAddModfile(void* object, int mod_id, ModioModfileHandler* modfile_handler, void (*callback)(void* object, ModioResponse response, const ModioModfile& modfile));
  void MODIO_DLL modioEditModfile(void* object, int mod_id, int modfile_id, ModioModfileHandler* modfile_handler, void (*callback)(void* object, ModioResponse response, const ModioModfile& modfile));
  void MODIO_DLL modioInstallModfile(void* object, u32 modfile_id, char* modfile_download, char* destination_path, void (*callback)(void* object, ModioResponse response, char* path));
  int MODIO_DLL modioGetModfileState(int modfile_id);
  double MODIO_DLL modioGetModfileDownloadPercentage(int modfile_id);
}

#endif
