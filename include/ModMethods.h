#ifndef MODIO_MOD_METHODS_H
#define MODIO_MOD_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"
#include "Filter.h"
#include "handlers/ModHandler.h"

namespace modio
{
  MODIO_DLL void getMods(Filter* filter, function< void(int response_code, string message, vector<Mod*>) > callback);
  MODIO_DLL void addMod(ModHandler* add_mod_handler, function<void(int response_code, string message, Mod* mod)> callback);
  MODIO_DLL void editMod(Mod* mod, ModHandler* add_mod_handler, function<void(int response_code, string message, Mod* mod)> callback);
  MODIO_DLL void deleteMod(Mod* mod, function<void(int response_code, string message, Mod* mod)> callback);

  MODIO_DLL void downloadModLogoThumbnail(Mod *mod, function< void(int response_code, string message, Mod* mod, string path) > callback);
  MODIO_DLL void downloadModLogoFull(Mod *mod, function< void(int response_code, string message, Mod* mod, string path) > callback);
  MODIO_DLL void downloadModMediaImagesThumbnail(Mod *mod, function< void(int response_code, string message, Mod* mod, vector<string> paths) > callback);
  MODIO_DLL void downloadModMediaImagesFull(Mod *mod, function< void(int response_code, string message, Mod* mod, vector<string> paths) > callback);
  MODIO_DLL void installMod(Mod *mod, string destination_path, function< void(int response_code, string message, Mod*mod, string path) > callback);
}

#endif
