#ifndef MODIO_AUTHENTICATION_H
#define MODIO_AUTHENTICATION_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "Globals.h"
#include <thread>

namespace modio
{
  MODIO_DLL void emailExchange(string security_code, function< void(int response_code, string message) > callback);
  MODIO_DLL void emailRequest(string email, function< void(int response_code, string message) > callback);
  MODIO_DLL bool isLoggedIn();
  MODIO_DLL void logout();
}

#endif
