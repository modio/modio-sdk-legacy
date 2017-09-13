#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "CurlWrapper.h"
#include "MinizipWrapper.h"
#include "Globals.h"

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
  struct EmailExchangeParams
  {
    function<void(int)> callback;
  };

  void MODWORKS_DLL emailExchange(string security_code, function< void(int response) > callback);
  void MODWORKS_DLL emailRequest(string email, function< void(int response) > callback);
  bool MODWORKS_DLL isLoggedIn();
  void MODWORKS_DLL logout();
}

#endif
