#ifndef MODIO_TAGCALLBACKS_H
#define MODIO_TAGCALLBACKS_H

#include "../../../Globals.h"
#include "../../schemas/ModioResponse.h"
#include "../../schemas/ModioTag.h"

struct GetModTagsParams
{
  void* object;
  void (*callback)(void* object, ModioResponse response, ModioTag* tags_array, u32 tags_array_size);
};

struct EditTagsParams
{
  void* object;
  void (*callback)(void* object, ModioResponse response);
};

struct DeleteModTagsParams
{
  void* object;
  void (*callback)(void* object, ModioResponse response);
};

extern std::map< u32, GetModTagsParams* > get_mod_tags_callbacks;
extern std::map< u32, EditTagsParams* > add_mod_tags_callbacks;
extern std::map< u32, DeleteModTagsParams* > delete_mod_tags_callbacks;

void modioOnGetModTags(u32 call_number, u32 response_code, nlohmann::json response_json);
void modioOnTagsAdded(u32 call_number, u32 response_code, nlohmann::json response_json);
void modioOnTagsDeleted(u32 call_number, u32 response_code, nlohmann::json response_json);

#endif
