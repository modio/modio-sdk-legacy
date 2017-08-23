#ifndef MODWORKS_CURL_WRAPPER_H
#define MODWORKS_CURL_WRAPPER_H

#include <stdio.h>
#include <iostream>
#include <map>
#include "json/json.hpp"
#include "curl/curl.h"
#include "MinizipWrapper.h"
#include "Utility.h"
#include "Mod.h"

#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERIFICATION

namespace modworks
{
  class Mod;

  using namespace std;
  using json = nlohmann::json;

  int getCallCount();
  int getOngoingCall();
  void advanceCallCount();
  void advanceOngoingCall();

  class GetJsonHandler
  {
  public:
    string response;
    function< void(vector<modworks::Mod*>) > callback;
    GetJsonHandler(function< void(vector<modworks::Mod*>) > callback);
  };

  void getJson(string url, vector<string> headers, function< void(vector<modworks::Mod*>) > callback, int call_number);

  class DownloadFileHandler
  {
  public:
    function< void(int, modworks::Mod*) > callback;
    DownloadFileHandler(function< void(int, modworks::Mod*) > callback);
  };

  double curlGetFileSize(string url);

  void downloadModFile(modworks::Mod* mod, string url, string path, function< void(int, modworks::Mod*, string) > callback, int call_number);

  class DownloadRedirectHandler
  {
  public:
    modworks::Mod* mod;
    string path;
    string destination_path;
    function< void(int, modworks::Mod*, string) > callback;
    int call_number;
    DownloadRedirectHandler(modworks::Mod* mod, string path, string destination_path, function< void(int, Mod*, string) > callback, int call_number);
  };

  void downloadRedirect(modworks::Mod* mod, string url, string path, string destination_path, function< void(int, modworks::Mod*, string) > callback, int call_number);
  void downloadZipFile(modworks::Mod* mod, string url, string path, string downloadZipFile, function< void(int, modworks::Mod*, string) > callback, int call_number);
}

#endif
