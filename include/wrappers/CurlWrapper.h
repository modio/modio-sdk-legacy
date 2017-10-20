#ifndef MODIO_CURL_WRAPPER_H
#define MODIO_CURL_WRAPPER_H

#include <stdio.h>
#include <iostream>
#include <map>
#include "dependencies/json/json.hpp"
#include "dependencies/curl/curl.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Response.h"
#include "Utility.h"

#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERIFICATION

using namespace std;
using json = nlohmann::json;

namespace modio
{
  namespace curlwrapper
  {
    void initCurl();
    int getCallCount();
    int getOngoingCall();
    void advanceCallCount();
    void advanceOngoingCall();
    void cleanCallQueue();

    class JsonResponseHandler
    {
    public:
      string response;
      JsonResponseHandler();
    };

    struct CurrentDownloadHandle
    {
      CURL* curl;
      string path;
      bool pause_flag;
    };

    CurrentDownloadInfo getCurrentDownloadInfo();
    void pauseCurrentDownload();
    void shutdownCurl();
    void download(int call_number, string url, string path, function< void(int call_number, ModioResponse* response, string url, string path) > callback);
    void get(int call_number, string url, vector<string> headers, function<void(int call_number, ModioResponse* modio_response, json response_json)> callback);
    void post(int call_number, string url, vector<string> headers, map<string, string> data, function<void(int call_number, ModioResponse* response, json response_json)> callback);
    void put(int call_number, string url, vector<string> headers, multimap<string, string> data, function<void(int call_number, ModioResponse* response, json response_json)> callback);
    void postForm(int call_number, string url, vector<string> headers, multimap<string, string> curlform_copycontents, map<string, string> curlform_files, function<void(int call_number, ModioResponse* modio_response, json response_json)> callback);
    void deleteCall(int call_number, string url, vector<string> headers, function<void(int call_number, ModioResponse* response, json response_json)> callback);
  }
}

#endif
