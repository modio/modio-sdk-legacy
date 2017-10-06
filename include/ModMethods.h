#ifndef MOD_METHODS
#define MOD_METHODS

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"
#include "Filter.h"

namespace modworks
{
  class AddModHandler
  {
  public:
    map<string, string> curlform_copycontents;
    map<string, string> curlform_files;
    void setLogoPath(string logo_path);
    void setName(string name);
    void setHomepage(string homepage);
    void setSummary(string summary);
    void setPrice(double price);
    void setStock(int stock);
    void setDescription(string description);
    void setMetadata(string metadata);
    void setNameid(string nameid);
    void setModfile(int modfile);
  };

  class AddModFileHandler
  {
  public:
    map<string, string> curlform_copycontents;
    string path;
    void setPath(string path);
    void setVersion(string version);
    void setChangelog(string changelog);
    void setActive(string active);
  };

  void MODWORKS_DLL getMods(Filter* filter, function< void(int, vector<Mod*>) > callback);

  void MODWORKS_DLL addMod(AddModHandler* add_mod_handler, function<void(int, Mod*)> callback);
  void MODWORKS_DLL addModFile(Mod* mod, AddModFileHandler* add_mod_file_handler, function<void(int, Mod*)> callback);
  void MODWORKS_DLL editMod(Mod* mod, AddModHandler* add_mod_handler, function<void(int, Mod*)> callback);
  void MODWORKS_DLL deleteMod(Mod* mod, function<void(int, Mod*)> callback);

  void MODWORKS_DLL downloadModLogoThumbnail(Mod *mod, function< void(int, Mod*, string) > callback);
  void MODWORKS_DLL downloadModLogoFull(Mod *mod, function< void(int, Mod*, string) > callback);
  void MODWORKS_DLL downloadModMediaImagesThumbnail(Mod *mod, function< void(int, Mod*, vector<string>) > callback);
  void MODWORKS_DLL downloadModMediaImagesFull(Mod *mod, function< void(int, Mod*, vector<string>) > callback);
  void MODWORKS_DLL installMod(Mod *mod, string destination_path, function< void(int, Mod*, string) > callback);
}

#endif
