#ifndef MODIO_MOD_HANDLER_H
#define MODIO_MOD_HANDLER_H

#include "Globals.h"
#include "Utility.h"

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
    char* logo;
    char* name;
    char* homepage;
    char* summary;
    char* price;
    char* stock;
    char* description;
    char* metadata;
    char* nameid;
    char* modfile;
    Node* tags;
  };

  void MODIO_DLL modioInitModHandler(ModioModHandler* mod_handler);
  void MODIO_DLL modioSetLogoPath(ModioModHandler* mod_handler, char* logo_path);
  void MODIO_DLL modioSetName(ModioModHandler* mod_handler, char* name);
  void MODIO_DLL modioSetHomepage(ModioModHandler* mod_handler, char* homepage);
  void MODIO_DLL modioSetSummary(ModioModHandler* mod_handler, char* summary);
  void MODIO_DLL modioSetPrice(ModioModHandler* mod_handler, double price);
  void MODIO_DLL modioSetStock(ModioModHandler* mod_handler, int stock);
  void MODIO_DLL modioSetDescription(ModioModHandler* mod_handler, char* description);
  void MODIO_DLL modioSetMetadata(ModioModHandler* mod_handler, char* metadata);
  void MODIO_DLL modioSetNameid(ModioModHandler* mod_handler, char* nameid);
  void MODIO_DLL modioSetModfile(ModioModHandler* mod_handler, int modfile);
  void MODIO_DLL modioAddTag(ModioModHandler* mod_handler, char* tag);
  void MODIO_DLL modioFreeModHandler(ModioModHandler* mod_handler);
}

namespace modio
{
  map<string, string> getModfileCurlFormFilesParams(ModioModHandler* mod_handler);
  multimap<string, string> getModfileCurlFormCopyContentsParams(ModioModHandler* mod_handler);
}

#endif
