#include "c/methods/callbacks/MediaCallbacks.h"

std::map< u32, GenericRequestParams* > add_mod_logo_callbacks;
std::map< u32, GenericRequestParams* > add_mod_images_callbacks;
std::map< u32, GenericRequestParams* > add_mod_youtube_links_callbacks;
std::map< u32, GenericRequestParams* > add_mod_sketchfab_links_callbacks;
std::map< u32, GenericRequestParams* > delete_mod_images_callbacks;
std::map< u32, GenericRequestParams* > delete_mod_youtube_links_callbacks;
std::map< u32, GenericRequestParams* > delete_mod_sketchfab_links_callbacks;

void modioOnAddModLogo(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  add_mod_logo_callbacks[call_number]->callback(add_mod_logo_callbacks[call_number]->object, response);
  
  delete add_mod_logo_callbacks[call_number];
  add_mod_logo_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnAddModImages(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  add_mod_images_callbacks[call_number]->callback(add_mod_images_callbacks[call_number]->object, response);
  delete add_mod_images_callbacks[call_number];
  
  add_mod_images_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnAddModYoutubeLinks(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  add_mod_youtube_links_callbacks[call_number]->callback(add_mod_youtube_links_callbacks[call_number]->object, response);
  delete add_mod_youtube_links_callbacks[call_number];
  
  add_mod_youtube_links_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnAddModSketchfabLinks(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  add_mod_sketchfab_links_callbacks[call_number]->callback(add_mod_sketchfab_links_callbacks[call_number]->object, response);
  
  delete add_mod_sketchfab_links_callbacks[call_number];
  add_mod_sketchfab_links_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnDeleteModImages(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  delete_mod_images_callbacks[call_number]->callback(delete_mod_images_callbacks[call_number]->object, response);
  
  delete delete_mod_images_callbacks[call_number];
  delete_mod_images_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnDeleteModYoutubeLinks(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  delete_mod_youtube_links_callbacks[call_number]->callback(delete_mod_youtube_links_callbacks[call_number]->object, response);
  
  delete delete_mod_youtube_links_callbacks[call_number];
  delete_mod_youtube_links_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnDeleteModSketchfabLinks(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  delete_mod_sketchfab_links_callbacks[call_number]->callback(delete_mod_sketchfab_links_callbacks[call_number]->object, response);
  
  delete delete_mod_sketchfab_links_callbacks[call_number];
  delete_mod_sketchfab_links_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void clearMediaCallbackParams()
{
  for (auto add_mod_logo_callback : add_mod_logo_callbacks)
    delete add_mod_logo_callback.second;
  add_mod_logo_callbacks.clear();

  for (auto add_mod_images_callback : add_mod_images_callbacks)
    delete add_mod_images_callback.second;
  add_mod_images_callbacks.clear();

  for (auto add_mod_youtube_links_callback : add_mod_youtube_links_callbacks)
    delete add_mod_youtube_links_callback.second;
  add_mod_youtube_links_callbacks.clear();

  for (auto add_mod_sketchfab_links_callback : add_mod_sketchfab_links_callbacks)
    delete add_mod_sketchfab_links_callback.second;
  add_mod_sketchfab_links_callbacks.clear();

  for (auto delete_mod_images_callback : delete_mod_images_callbacks)
    delete delete_mod_images_callback.second;
  delete_mod_images_callbacks.clear();

  for (auto delete_mod_youtube_links_callback : delete_mod_youtube_links_callbacks)
    delete delete_mod_youtube_links_callback.second;
  delete_mod_youtube_links_callbacks.clear();

  for (auto delete_mod_sketchfab_links_callback : delete_mod_sketchfab_links_callbacks)
    delete delete_mod_sketchfab_links_callback.second;
  delete_mod_sketchfab_links_callbacks.clear();
}