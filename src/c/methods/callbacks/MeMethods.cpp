#include "c/methods/callbacks/MeCallbacks.h"

std::map< u32, GetAuthenticatedUserParams* > get_authenticated_user_callbacks;

void modioOnGetAuthenticatedUser(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioUser user;
  modioInitUser(&user, response_json);

  get_authenticated_user_callbacks[call_number]->callback(get_authenticated_user_callbacks[call_number]->object, response, user);

  delete get_authenticated_user_callbacks[call_number];
  get_authenticated_user_callbacks.erase(call_number);
  modioFreeResponse(&response);
}
