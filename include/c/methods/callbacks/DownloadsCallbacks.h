#ifndef MODIO_DOWNLOADSCALLBACKS_H
#define MODIO_DOWNLOADSCALLBACKS_H

#include "c/schemas/ModioResponse.h"
#include "wrappers/MinizipWrapper.h"
#include "wrappers/CurlWrapper.h"
#include "Globals.h"
#include "ModUtility.h"

struct GetInstallModParams
{
  u32 mod_id;
  void* object;
  std::string destination_path;
  void (*callback)(void* object, ModioResponse response);
};

struct InstallModParams
{
  u32 mod_id;
  json mod_json;
  u32 get_install_mod_call;
  void* object;
  u32 modfile_id;
  std::string zip_path;
  std::string destination_path;
  FILE* file;
  void (*callback)(void* object, ModioResponse response);
};

extern std::map< u32, GetInstallModParams* > get_install_mod_callbacks;
extern std::map< u32, InstallModParams* > install_mod_callbacks;

void modioOnModDownloaded(u32 call_number, u32 response_code);
void onGetInstallMod(u32 call_number, u32 response_code, json response_json);

#endif
