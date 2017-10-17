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

extern "C"
{
  void MODIO_DLL modioEmailRequest(char* email, void (*callback)(int response_code, char* message));
  void MODIO_DLL modioEmailExchange(char* security_code, void (*callback)(int response_code, char* message));
  bool MODIO_DLL modioIsLoggedIn();
  void MODIO_DLL modioLogout();
}

#endif
