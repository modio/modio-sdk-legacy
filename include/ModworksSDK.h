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
  class MODWORKS_DLL SDK;
  
  struct EmailExchangeParams
  {
    function<void(int)> callback;
	SDK* sdk;
  };

  struct AddModParams
  {
    string directory_path;
    string version;
    string changelog;
    function<void(int, Mod*)> callback;
	SDK* sdk;
  };

  class SDK
  {
  public:
    string api_key;
    string access_token;
    int game_id;

    string directory_path;
    string version;
    string changelog;

    SDK(int game_id, string api_key);

    //GET methods
    void getMods(function< void(int, vector<Mod*>) > callback);

    //POST methods
    void emailExchange(string security_code, function< void(int response) > callback);
    void emailRequest(string email, function< void(int response) > callback);
    void addMod(/*Mod params*/string name, string homepage, string summary, string logo_path,
                /*File params*/string directory_path, string version, string changelog,
                /*Callback*/ function< void(int, Mod*) > callback);

    void addFile(Mod *mod, string directory_path, string version, string changelog, function<void(int, Mod*)> callback);
    void downloadLogoThumbnail(Mod *mod, function< void(int, Mod*, string) > callback);
    void download(Mod *mod, string destination_path, function< void(int, Mod*, string) > callback);
  };
}

#endif
