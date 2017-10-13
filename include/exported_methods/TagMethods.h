#ifndef MODIO_MOD_METHODS_H
#define MODIO_MOD_METHODS_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"

namespace modio
{
  void MODIO_DLL getTags(Mod* mod, function<void(int response_code, string message, Mod* mod, vector<string> tags)> callback);
  void MODIO_DLL addTags(Mod* mod, vector<string> tags, function<void(int response_code, string message, Mod* mod)> callback);
  void MODIO_DLL deleteTags(Mod* mod, vector<string> tags, function<void(int response_code, string message, Mod* mod)> callback);
}

#endif
