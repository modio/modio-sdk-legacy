#ifndef MODIO_MOD_METHODS_H
#define MODIO_MOD_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"
#include "Filter.h"
#include "handlers/ModHandler.h"

#ifdef WINDOWS
#  ifdef BUILDING_MODIO_DLL
#    define MODIO_DLL __declspec(dllexport)
#  else
#    define MODIO_DLL __declspec(dllimport)
#  endif
#else
#  define MODIO_DLL
#endif

extern "C"
{
  void MODIO_DLL getMods(ModioFilter* filter, void (*callback)(int response_code, char* message, ModioMod* mods, int mods_size));
  void MODIO_DLL addMod(ModHandler* add_mod_handler, void (*callback)(int response_code, char* message, ModioMod* mod));
  void MODIO_DLL editMod(ModioMod* mod, ModHandler* add_mod_handler, void (*callback)(int response_code, char* message, ModioMod* mod));
  void MODIO_DLL deleteMod(ModioMod* mod, void (*callback)(int response_code, char* message, ModioMod* mod));
/*
  void MODIO_DLL downloadModLogoThumbnail(Mod *mod, function< void(int response_code, string message, Mod* mod, string path) > callback);
  void MODIO_DLL downloadModLogoFull(Mod *mod, function< void(int response_code, string message, Mod* mod, string path) > callback);
  void MODIO_DLL downloadModMediaImagesThumbnail(Mod *mod, function< void(int response_code, string message, Mod* mod, vector<string> paths) > callback);
  void MODIO_DLL downloadModMediaImagesFull(Mod *mod, function< void(int response_code, string message, Mod* mod, vector<string> paths) > callback);
  void MODIO_DLL installMod(Mod *mod, string destination_path, function< void(int response_code, string message, Mod*mod, string path) > callback);
*/
}

#endif
