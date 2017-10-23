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

extern "C"
{
  struct ModioModHandler
  {
    multimap<string, string> curlform_copycontents;
    map<string, string> curlform_files;
  };

  void MODIO_DLL modioSetLogoPath(ModioModHandler* mod_handler, string logo_path);
  void MODIO_DLL modioSetName(ModioModHandler* mod_handler, string name);
  void MODIO_DLL modioSetHomepage(ModioModHandler* mod_handler, string homepage);
  void MODIO_DLL modioSetSummary(ModioModHandler* mod_handler, string summary);
  void MODIO_DLL modioSetPrice(ModioModHandler* mod_handler, double price);
  void MODIO_DLL modioSetStock(ModioModHandler* mod_handler, int stock);
  void MODIO_DLL modioSetDescription(ModioModHandler* mod_handler, string description);
  void MODIO_DLL modioSetMetadata(ModioModHandler* mod_handler, string metadata);
  void MODIO_DLL modioSetNameid(ModioModHandler* mod_handler, string nameid);
  void MODIO_DLL modioSetModfile(ModioModHandler* mod_handler, int modfile);
  void MODIO_DLL modioAddTag(ModioModHandler* mod_handler, string tag);
}

#endif
