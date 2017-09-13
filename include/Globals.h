#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
using namespace std;

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
  extern string api_key;
  extern string access_token;
  extern int game_id;
}

#endif
