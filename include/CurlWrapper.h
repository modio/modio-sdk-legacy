#ifndef CURL_WRAPPER_H
#define CURL_WRAPPER_H

#include <stdio.h>
#include <iostream>
#include <map>
#include "json/json.hpp"
#include "curl/curl.h"
#include "MinizipWrapper.h"
#include "Utility.h"
#include "Mod.h"

class Mod;

#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERIFICATION

using namespace std;
using json = nlohmann::json;

class GetJsonHandler
{
public:
  string response;
  function< void(vector<Mod*>) > callback;
  GetJsonHandler(function< void(vector<Mod*>) > callback);
};

void getJson(string url, vector<string> headers, function< void(vector<Mod*>) > callback);

class DownloadFileHandler
{
public:
  function< void(int, Mod*) > callback;
  DownloadFileHandler(function< void(int, Mod*) > callback);
};

double curlGetFileSize(string url);

void downloadModFile(Mod* mod, string url, string path, function< void(int, Mod*, string) > callback);

class DownloadRedirectHandler
{
public:
  Mod* mod;
  string path;
  string destination_path;
  function< void(int, Mod*, string) > callback;
  DownloadRedirectHandler(Mod* mod, string path, string destination_path, function< void(int, Mod*, string) > callback);
};

void downloadRedirect(Mod* mod, string url, string path, string destination_path, function< void(int, Mod*, string) > callback);
void downloadZipFile(Mod* mod, string url, string path, string downloadZipFile, function< void(int, Mod*, string) > callback);

#endif
