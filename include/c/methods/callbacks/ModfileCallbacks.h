#ifndef MODIO_MODFILECALLBACKS_H
#define MODIO_MODFILECALLBACKS_H

#include "c/schemas/ModioResponse.h"
#include "Globals.h"
#include "c/schemas/ModioModfile.h"

struct AddModfileParams
{
  void* object;
  void (*callback)(void* object, ModioResponse response, ModioModfile modfile);
};

struct EditModfileParams
{
  void* object;
  u32 modfile_id;
  void (*callback)(void* object, ModioResponse response, ModioModfile modfile);
};

extern std::map< u32, AddModfileParams* > add_modfile_callbacks;
extern std::map< u32, EditModfileParams* > edit_modfile_callbacks;

void modioOnModfileAdded(u32 call_number, u32 response_code, json response_json);
void modioOnModfileEdited(u32 call_number, u32 response_code, json response_json);

#endif
