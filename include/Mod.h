#ifndef MODWORKS_MOD_H
#define MODWORKS_MOD_H

#include <thread>
#include "json/json.hpp"
#include "CurlWrapper.h"

using namespace std;
using json = nlohmann::json;

namespace modworks
{
  class Mod;

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

  class Mod
  {
  public:
    int id;
    int game;
    string logo_url;
    string logo_thumbnail_url;
    string name;
    string summary;
    string description;
    string download_url;

    Mod(json mod_json);
  };
}

#endif
