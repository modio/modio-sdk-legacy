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
  class ModHandler
  {
  public:
    map<string, string> curlform_copycontents;
    map<string, string> curlform_files;
    void MODIO_DLL setLogoPath(string logo_path);
    void MODIO_DLL setName(string name);
    void MODIO_DLL setHomepage(string homepage);
    void MODIO_DLL setSummary(string summary);
    void MODIO_DLL setPrice(double price);
    void MODIO_DLL setStock(int stock);
    void MODIO_DLL setDescription(string description);
    void MODIO_DLL setMetadata(string metadata);
    void MODIO_DLL setNameid(string nameid);
    void MODIO_DLL setModfile(int modfile);
  };
}

#endif
