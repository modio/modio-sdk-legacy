#ifndef MODIO_SDK_H
#define MODIO_SDK_H

//#pragma warning(disable : 4503)

#include "Globals.h"
#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "extern_c/schemas/ModioMod.h"
#include "extern_c/methods/AuthenticationMethods.h"
#include "extern_c/methods/ModMethods.h"
#include "extern_c/methods/ModfileMethods.h"
#include "extern_c/methods/TagMethods.h"
#include "extern_c/methods/ImageMethods.h"
#include "instance/ModIOInstance.h"

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
