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

using namespace std;
using json = nlohmann::json;

namespace modworks
{
  class Mod;

  void initCurl();
  int getCallCount();
  int getOngoingCall();
  void advanceCallCount();
  void advanceOngoingCall();

  class JsonResponseHandler
  {
  public:
    string response;
    JsonResponseHandler();
  };

  void download(int call_number, string url, string path, function< void(int, int, string, string) > callback);
  void get(int call_number, string url, vector<string> headers, function<void(int call_number, json response)> callback);
  void post(int call_number, string url, map<string, string> data, function<void(int call_number, json response)> callback);
  void postForm(int call_number, string url, vector<string> headers, map<string, string> curlform_copycontents, map<string, string> curlform_files, function<void(int call_number, json response)> callback);
}

#endif
