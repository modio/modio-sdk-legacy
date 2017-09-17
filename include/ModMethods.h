#ifndef MOD_METHODS
#define MOD_METHODS

#include "CurlWrapper.h"
#include "MinizipWrapper.h"
#include "Mod.h"
#include "Globals.h"

namespace modworks
{
  struct AddFileParams
  {
    Mod* mod;
    function< void(int, Mod*) > callback;
  };

  struct DownloadThumbnailParams
  {
    Mod* mod;
    function< void(int, Mod*, string) > callback;
  };

  struct DownloadModfileParams
  {
    Mod* mod;
    string destination_path;
    function< void(int, Mod*, string) > callback;
  };

  void MODWORKS_DLL getMods(function< void(int, vector<Mod*>) > callback);

  void MODWORKS_DLL addMod(/*Mod params*/string name, string homepage, string summary, string logo_path,
              /*File params*/string directory_path, string version, string changelog,
              /*Callback*/ function< void(int, Mod*) > callback);

  void MODWORKS_DLL addFile(Mod *mod, string directory_path, string version, string changelog, function<void(int, Mod*)> callback);
  void MODWORKS_DLL downloadLogoThumbnail(Mod *mod, function< void(int, Mod*, string) > callback);
  void MODWORKS_DLL download(Mod *mod, string destination_path, function< void(int, Mod*, string) > callback);
}

#endif
