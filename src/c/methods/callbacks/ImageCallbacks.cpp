#include "c/methods/callbacks/ImageCallbacks.h"

std::map< u32, DownloadImageParams* > download_image_callbacks;
std::map< u32, EditModLogoParams* > edit_mod_logo_callbacks;

void modioOnImageDownloaded(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  fclose(download_image_callbacks[call_number]->file);
  download_image_callbacks[call_number]->callback(download_image_callbacks[call_number]->object, response);
  delete download_image_callbacks[call_number];
  download_image_callbacks.erase(call_number);
  modioFreeResponse(&response);
}

void modioOnModLogoEdited(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  edit_mod_logo_callbacks[call_number]->callback(edit_mod_logo_callbacks[call_number]->object, response, edit_mod_logo_callbacks[call_number]->mod_id);
  delete edit_mod_logo_callbacks[call_number];
  edit_mod_logo_callbacks.erase(call_number);
  modioFreeResponse(&response);
}
