#ifndef CURL_WRAPPER_H
#define CURL_WRAPPER_H

#include <json/json.hpp>
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <map>
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
  function< void(int) > callback;
  DownloadFileHandler(function< void(int) > callback);
};

double curlGetFileSize(string url);
void downloadFile(string url, string download_path, function< void(int) > callback);

#endif
