#ifndef MODIO_MODFILE_METHODS_H
#define MODIO_MODFILE_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"
#include "handlers/ModfileHandler.h"

extern "C"
{
  void MODIO_DLL modioAddModfile(ModioMod* mod, ModfileHandler* modfile_handler, void (*callback)(ModioResponse* response, ModioModfile* modfile));
  void MODIO_DLL modioEditModfile(ModioModfile* modfile, ModfileHandler* modfile_handler, void (*callback)(ModioResponse* response, ModioModfile* modfile));
}

#endif
