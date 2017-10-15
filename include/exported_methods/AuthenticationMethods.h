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
  namespace modio
  {
    void MODIO_DLL emailRequest(char* email, void (*callback)(int response_code, char* message));
    void MODIO_DLL emailExchange(char* security_code, void (*callback)(int response_code, char* message));
    bool MODIO_DLL isLoggedIn();
    void MODIO_DLL logout();
  }
}

#endif
