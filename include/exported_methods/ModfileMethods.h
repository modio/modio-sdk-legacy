#ifndef MODIO_MODFILE_METHODS_H
#define MODIO_MODFILE_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"
#include "handlers/ModfileHandler.h"

namespace modio
{
  MODIO_DLL void addModfile(ModioMod* mod, ModfileHandler* add_mod_file_handler, function<void(int response_code, string message, ModioMod* mod)> callback);
  MODIO_DLL void editModfile(ModioModfile* modfile, ModfileHandler* modfile_handler, function<void(int response_code, string message, ModioModfile* modfile)> callback);
}

#endif
