#ifndef MODIO_IMAGECALLBACKS_H
#define MODIO_IMAGECALLBACKS_H

#include "c/schemas/ModioResponse.h"
#include "Globals.h"

struct DownloadImageParams
{
  void* object;
  std::string destination_path;
  FILE* file;
  void (*callback)(void* object, ModioResponse response);
};

struct EditModLogoParams
{
  void* object;
  u32 mod_id;
  void (*callback)(void* object, ModioResponse response, u32 mod_id);
};

extern std::map< u32, DownloadImageParams* > download_image_callbacks;
extern std::map< u32, EditModLogoParams* > edit_mod_logo_callbacks;

void modioOnImageDownloaded(u32 call_number, u32 response_code);
void modioOnModLogoEdited(u32 call_number, u32 response_code, json response_json);

#endif
