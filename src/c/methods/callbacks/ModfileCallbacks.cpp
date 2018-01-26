#include "c/methods/callbacks/ModfileCallbacks.h"

std::map< u32, AddModfileParams* > add_modfile_callbacks;
std::map< u32, EditModfileParams* > edit_modfile_callbacks;

void modioOnModfileAdded(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioModfile modfile;
  modioInitModfile(&modfile, response_json);

  add_modfile_callbacks[call_number]->callback(add_modfile_callbacks[call_number]->object, response, modfile);
  delete add_modfile_callbacks[call_number];
  add_modfile_callbacks.erase(call_number);
  modioFreeResponse(&response);
  modioFreeModfile(&modfile);
}

void modioOnModfileEdited(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioModfile modfile;
  modioInitModfile(&modfile, response_json);

  edit_modfile_callbacks[call_number]->callback(edit_modfile_callbacks[call_number]->object, response, modfile);
  delete edit_modfile_callbacks[call_number];
  edit_modfile_callbacks.erase(call_number);
  modioFreeResponse(&response);
  modioFreeModfile(&modfile);
}
