#ifndef MODIO_MODFILE_METHODS_H
#define MODIO_MODFILE_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"
#include "handlers/ModfileHandler.h"

namespace modio
{
  void MODIO_DLL addModfile(Mod* mod, ModfileHandler* add_mod_file_handler, function<void(int response_code, string message, Mod* mod)> callback);
}

#endif
