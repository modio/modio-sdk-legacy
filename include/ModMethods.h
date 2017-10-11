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
  void MODIO_DLL getMods(Filter* filter, function< void(int response_code, string message, vector<Mod*>) > callback);
  void MODIO_DLL addMod(ModHandler* add_mod_handler, function<void(int response_code, string message, Mod* mod)> callback);
  void MODIO_DLL editMod(Mod* mod, ModHandler* add_mod_handler, function<void(int response_code, string message, Mod* mod)> callback);
  void MODIO_DLL deleteMod(Mod* mod, function<void(int response_code, string message, Mod* mod)> callback);
  void MODIO_DLL addTags(Mod* mod, vector<string> tags, function<void(int response_code, string message, Mod* mod)> callback);

  void MODIO_DLL downloadModLogoThumbnail(Mod *mod, function< void(int response_code, string message, Mod* mod, string path) > callback);
  void MODIO_DLL downloadModLogoFull(Mod *mod, function< void(int response_code, string message, Mod* mod, string path) > callback);
  void MODIO_DLL downloadModMediaImagesThumbnail(Mod *mod, function< void(int response_code, string message, Mod* mod, vector<string> paths) > callback);
  void MODIO_DLL downloadModMediaImagesFull(Mod *mod, function< void(int response_code, string message, Mod* mod, vector<string> paths) > callback);
  void MODIO_DLL installMod(Mod *mod, string destination_path, function< void(int response_code, string message, Mod*mod, string path) > callback);
}

#endif
