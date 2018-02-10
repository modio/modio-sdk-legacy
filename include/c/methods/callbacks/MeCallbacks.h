#ifndef MODIO_MECALLBACKS_H
#define MODIO_MECALLBACKS_H

#include "c/schemas/ModioResponse.h"
#include "c/schemas/ModioUser.h"
#include "Globals.h"

struct GetAuthenticatedUserParams
{
  void* object;
  void (*callback)(void* object, ModioResponse response, ModioUser user);
};

extern std::map< u32, GetAuthenticatedUserParams* > get_authenticated_user_callbacks;

void modioOnGetAuthenticatedUser(u32 call_number, u32 response_code, json response_json);

#endif
