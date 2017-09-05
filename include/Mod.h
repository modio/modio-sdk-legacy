#ifndef MODWORKS_MOD_H
#define MODWORKS_MOD_H

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

    map< int, function<void(int, Mod*)> > add_file_callbacks;
    map< int, function< void(int, Mod*, string) > > download_thumbnail_callbacks;
    map< int, function< void(int, Mod*, string) > > download_modfile_callbacks;

    Mod(json mod_json);
    void onThumbnailDownloaded(int call_number, int status, string url, string path, map<string,string> params);
    void onModfileDownloaded(int call_number, int status, string url, string path, map<string,string> params);
    void onFileAdded(int call_number, json response, map<string, string> params);
    void addFile(string directory_path, string version, string changelog, function<void(int, Mod*)> callback);
    void downloadLogoThumbnail(function< void(int, Mod*, string) > callback);
    void download(string destination_path, function< void(int, Mod*, string) > callback);
  };
}

#endif
