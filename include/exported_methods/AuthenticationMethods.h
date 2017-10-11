#ifndef MODIO_AUTHENTICATION_H
#define MODIO_AUTHENTICATION_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "Globals.h"
#include <thread>

#ifdef WINDOWS
#  ifdef BUILDING_MODIO_DLL
#    define MODIO_DLL __declspec(dllexport)
#  else
#    define MODIO_DLL __declspec(dllimport)
#  endif
#else
#  define MODIO_DLL
#endif

namespace modio
{
  void MODIO_DLL emailExchange(string security_code, function< void(int response_code, string message) > callback);
  void MODIO_DLL emailRequest(string email, function< void(int response_code, string message) > callback);
  bool MODIO_DLL isLoggedIn();
  void MODIO_DLL logout();
}

#endif
