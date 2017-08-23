#ifndef MOD_H
#define MOD_H

#include <thread>
#include "json/json.hpp"
#include "CurlWrapper.h"

using namespace std;
using json = nlohmann::json;

namespace modworks
{
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
    void downloadLogoThumbnail(function< void(int, Mod*, string) > callback);
    void download(string destination_path, function< void(int, Mod*, string) > callback);
  };
}

#endif
