#ifndef MODIO_MOD_HANDLER_H
#define MODIO_MOD_HANDLER_H

#include "Globals.h"
#include "Utility.h"
#include "extern_c/ModioC.h"
#include "extern_c/schemas/ModioListNode.h"

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
  std::map<std::string, std::string> getModfileCurlFormFilesParams(ModioModHandler* mod_handler);
  std::multimap<std::string, std::string> getModfileCurlFormCopyContentsParams(ModioModHandler* mod_handler);
}

#endif
