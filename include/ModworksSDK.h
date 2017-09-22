#ifndef MODWORKS_SDK_H
#define MODWORKS_SDK_H

//#pragma warning(disable : 4503)

#include "CurlWrapper.h"
#include "MinizipWrapper.h"
#include "Mod.h"
#include "Globals.h"
#include "AuthenticationMethods.h"
#include "ModMethods.h"

namespace modworks
{
  void MODWORKS_DLL init(int game_id, string api_key);
  void MODWORKS_DLL init(int game_id, string api_key, string root_path);
  void MODWORKS_DLL setDebugMode(DebugMode debug_mode);
  void MODWORKS_DLL pauseCurrentDownload();
}

#endif
