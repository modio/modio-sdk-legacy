#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "Globals.h"
#include <thread>

#ifdef WINDOWS
#  ifdef BUILDING_MODWORKS_DLL
#    define MODWORKS_DLL __declspec(dllexport)
#  else
#    define MODWORKS_DLL __declspec(dllimport)
#  endif
#else
#  define MODWORKS_DLL
#endif

namespace modworks
{
  void MODWORKS_DLL emailExchange(string security_code, function< void(int response_code) > callback);
  void MODWORKS_DLL emailRequest(string email, function< void(int response_code) > callback);
  bool MODWORKS_DLL isLoggedIn();
  void MODWORKS_DLL logout();
}

#endif
