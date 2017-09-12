#ifndef MODWORKS_SDK_H
#define MODWORKS_SDK_H

#pragma warning(disable : 4503)

#include "CurlWrapper.h"
#include "MinizipWrapper.h"
#include "Mod.h"

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

  struct AddModParams
  {
    string directory_path;
    string version;
    string changelog;
    function<void(int, Mod*)> callback;
  };

  //Auth
  void MODWORKS_DLL emailExchange(string security_code, function< void(int response) > callback);
  void MODWORKS_DLL emailRequest(string email, function< void(int response) > callback);
  bool MODWORKS_DLL isLoggedIn();
  void MODWORKS_DLL logout();

  void MODWORKS_DLL init(int game_id, string api_key);

  //GET methods
  void MODWORKS_DLL getMods(function< void(int, vector<Mod*>) > callback);

  //POST methods
  void MODWORKS_DLL addMod(/*Mod params*/string name, string homepage, string summary, string logo_path,
              /*File params*/string directory_path, string version, string changelog,
              /*Callback*/ function< void(int, Mod*) > callback);

  void MODWORKS_DLL addFile(Mod *mod, string directory_path, string version, string changelog, function<void(int, Mod*)> callback);
  void MODWORKS_DLL downloadLogoThumbnail(Mod *mod, function< void(int, Mod*, string) > callback);
  void MODWORKS_DLL download(Mod *mod, string destination_path, function< void(int, Mod*, string) > callback);
}

#endif
