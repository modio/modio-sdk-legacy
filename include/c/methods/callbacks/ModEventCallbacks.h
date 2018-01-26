#ifndef MODIO_MODCALLBACKS_H
#define MODIO_MODCALLBACKS_H

#include "Globals.h"
#include "c/schemas/ModioResponse.h"
#include "c/schemas/ModioModEvent.h"

struct GetAllModEventsParams
{
  void* object;
  void (*callback)(void* object, ModioResponse response, ModioModEvent* mod_events_array, u32 mod_events_array_size);
};

extern std::map< u32, GetAllModEventsParams* > get_all_mod_events_callbacks;

void modioOnGetAllModEvents(u32 call_number, u32 response_code, json response_json);

#endif
