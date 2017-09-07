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

    map< int, AddFileParams* > add_file_callbacks;
    map< int, DownloadThumbnailParams* > download_thumbnail_callbacks;
    map< int, DownloadModfileParams* > download_modfile_callbacks;

    void onThumbnailDownloaded(int call_number, int status, string url, string path);
    void onModfileDownloaded(int call_number, int status, string url, string path);
    void onFileAdded(int call_number, json response);
    void addFile(string directory_path, string version, string changelog, function<void(int, Mod*)> callback);
    void downloadLogoThumbnail(function< void(int, Mod*, string) > callback);
    void download(string destination_path, function< void(int, Mod*, string) > callback);
  };
}

#endif
