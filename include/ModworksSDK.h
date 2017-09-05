#ifndef MODWORKS_SDK_H
#define MODWORKS_SDK_H

#include "CurlWrapper.h"
#include "MinizipWrapper.h"
#include "Mod.h"

namespace modworks
{
  class SDK
  {
  public:
    string api_key;
    string access_token;
    int game_id;

    string directory_path;
    string version;
    string changelog;

    map< int,function<void(int, Mod*)> > add_mod_callback;
    map< int,function<void(int)> > email_request_callbacks;
    map< int,function<void(int)> > email_exchange_callbacks;
    map< int,function<void(int, vector<Mod*>)> > get_mods_callbacks;

    SDK(int game_id, string api_key);

    //GET methods
    void onGetMods(int call_number, json response, map<string, string> params);
    void getMods(function< void(int, vector<Mod*>) > callback);

    //POST methods
    void emailExchange(string security_code, function< void(int response) > callback);
    void emailRequest(string email, function< void(int response) > callback);
    void addMod(/*Mod params*/string name, string homepage, string summary, string logo_path,
                /*File params*/string directory_path, string version, string changelog,
                /*Callback*/ function< void(int, Mod*) > callback);

    //Callbacks
    void onEmailRequested(int call_number, json response, map<string, string> params);
    void onEmailExchanged(int call_number, json response, map<string, string> params);
    void onModAdded(int call_number, json response, map<string, string> params);
  };
}

#endif
