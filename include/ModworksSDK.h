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

    SDK(int game_id, string api_key);

    //GET methods
    void getMods(function< void(vector<Mod*>) > callback);

    //POST methods
    void emailExchange(string security_code, function< void(int response) > callback);
    void emailRequest(string email, function< void(int response) > callback);
    void addMod(/*Mod params*/string name, string homepage, string summary, string logo_path, /*File params*/string directory_path, string version, string changelog);

    //Callbacks
    void onEmailRequested(json response, function< void(int response) > callback);
    void onEmailExchanged(json response, function< void(int) > callback);
    void onModAdded(json response, map<string, string> params);
  };
}

#endif
