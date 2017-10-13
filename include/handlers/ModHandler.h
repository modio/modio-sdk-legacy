#ifndef MODIO_MOD_HANDLER_H
#define MODIO_MOD_HANDLER_H

#include "Globals.h"

#ifdef WINDOWS
#  ifdef BUILDING_MODIO_DLL
#    define MODIO_DLL __declspec(dllexport)
#  else
#    define MODIO_DLL __declspec(dllimport)
#  endif
#else
#  define MODIO_DLL
#endif

namespace modio
{
  struct ModHandler
  {
    multimap<string, string> curlform_copycontents;
    map<string, string> curlform_files;
  };

  void MODIO_DLL setLogoPath(ModHandler* mod_handler, string logo_path);
  void MODIO_DLL setName(ModHandler* mod_handler, string name);
  void MODIO_DLL setHomepage(ModHandler* mod_handler, string homepage);
  void MODIO_DLL setSummary(ModHandler* mod_handler, string summary);
  void MODIO_DLL setPrice(ModHandler* mod_handler, double price);
  void MODIO_DLL setStock(ModHandler* mod_handler, int stock);
  void MODIO_DLL setDescription(ModHandler* mod_handler, string description);
  void MODIO_DLL setMetadata(ModHandler* mod_handler, string metadata);
  void MODIO_DLL setNameid(ModHandler* mod_handler, string nameid);
  void MODIO_DLL setModfile(ModHandler* mod_handler, int modfile);
  void MODIO_DLL addTag(ModHandler* mod_handler, string tag);
}

#endif
