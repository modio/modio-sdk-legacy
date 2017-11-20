#ifndef MODIO_SDK_H
#define MODIO_SDK_H

//#pragma warning(disable : 4503)

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"
#include "exported_methods/AuthenticationMethods.h"
#include "exported_methods/ModMethods.h"
#include "exported_methods/ModfileMethods.h"
#include "exported_methods/TagMethods.h"
#include "exported_methods/ImageMethods.h"

extern "C"
{
  void MODIO_DLL modioInit(int game_id, char* api_key);
  //void MODIO_DLL init(int game_id, char* api_key, char* root_path);
  void MODIO_DLL modioShutdown();
  //CurrentDownloadInfo MODIO_DLL modioGetCurrentDownloadInfo();
  void MODIO_DLL modioPauseCurrentDownload();
  void MODIO_DLL modioSetDebugLevel(unsigned int debug_level);
  void MODIO_DLL modioProcess();
}


#endif
