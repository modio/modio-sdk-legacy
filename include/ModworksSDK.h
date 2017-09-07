#ifndef MODWORKS_SDK_H
#define MODWORKS_SDK_H

#include "CurlWrapper.h"
#include "MinizipWrapper.h"
#include "Mod.h"

namespace modworks
{
  struct AddModParam
  {
    string directory_path;
    string version;
    string changelog;
    function<void(int, Mod*)> callback;
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

    map< int,AddModParam* > add_mod_callback;
    map< int,function<void(int)> > email_request_callbacks;
    map< int,function<void(int)> > email_exchange_callbacks;
    map< int,function<void(int, vector<Mod*>)> > get_mods_callbacks;

    SDK(int game_id, string api_key);

    //GET methods
    void onGetMods(int call_number, json response);
    void getMods(function< void(int, vector<Mod*>) > callback);

    //POST methods
    void emailExchange(string security_code, function< void(int response) > callback);
    void emailRequest(string email, function< void(int response) > callback);
    void addMod(/*Mod params*/string name, string homepage, string summary, string logo_path,
                /*File params*/string directory_path, string version, string changelog,
                /*Callback*/ function< void(int, Mod*) > callback);

    //Callbacks
    void onEmailRequested(int call_number, json response);
    void onEmailExchanged(int call_number, json response);
    void onModAdded(int call_number, json response);

    //Mod
    map< int, AddFileParams* > add_file_callbacks;
    map< int, DownloadThumbnailParams* > download_thumbnail_callbacks;
    map< int, DownloadModfileParams* > download_modfile_callbacks;

    void onThumbnailDownloaded(int call_number, int status, string url, string path);
    void onModfileDownloaded(int call_number, int status, string url, string path);
    void onFileAdded(int call_number, json response);

    void addFile(Mod *mod, string directory_path, string version, string changelog, function<void(int, Mod*)> callback);
    void downloadLogoThumbnail(Mod *mod, function< void(int, Mod*, string) > callback);
    void download(Mod *mod, string destination_path, function< void(int, Mod*, string) > callback);
  };
}

#endif
