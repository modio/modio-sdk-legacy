#ifndef MOD_METHODS
#define MOD_METHODS

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"
#include "Filter.h"

namespace modworks
{
  struct AddFileParams
  {
    Mod* mod;
    function< void(int, Mod*) > callback;
  };

  struct DownloadImageParams
  {
    Mod* mod;
    function< void(int, Mod*, string) > callback;
  };

  struct DownloadImagesParams
  {
    Mod* mod;
    int image_amount;
    vector<string> images;
    function< void(int, Mod*, vector<string>) > callback;
  };

  struct DownloadModfileParams
  {
    Mod* mod;
    string destination_path;
    function< void(int, Mod*, string) > callback;
  };

  void MODWORKS_DLL getMods(Filter* filter, function< void(int, vector<Mod*>) > callback);

  void MODWORKS_DLL addMod(/*Mod params*/string name, string homepage, string summary, string logo_path,
              /*File params*/string directory_path, string version, string changelog,
              /*Callback*/ function< void(int, Mod*) > callback);

  void MODWORKS_DLL addFile(Mod *mod, string directory_path, string version, string changelog, function<void(int, Mod*)> callback);
  void MODWORKS_DLL downloadModLogoThumbnail(Mod *mod, function< void(int, Mod*, string) > callback);
  void MODWORKS_DLL downloadModLogoFull(Mod *mod, function< void(int, Mod*, string) > callback);
  void MODWORKS_DLL downloadModMediaImagesThumbnail(Mod *mod, function< void(int, Mod*, vector<string>) > callback);
  void MODWORKS_DLL downloadModMediaImagesFull(Mod *mod, function< void(int, Mod*, vector<string>) > callback);
  void MODWORKS_DLL installMod(Mod *mod, string destination_path, function< void(int, Mod*, string) > callback);
}

#endif
