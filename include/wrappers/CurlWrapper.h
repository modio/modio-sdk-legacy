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
      std::string response;
      int call_number;
      std::function<void(int call_number, int response_code, json response_json)> callback;
      JsonResponseHandler(int call_number, std::function<void(int call_number, int response_code, json response_json)> callback);
    };

    struct CurrentDownloadHandle
    {
      CURL* curl;
      std::string path;
      bool pause_flag;
    };

    CurrentDownloadInfo getCurrentDownloadInfo();
    void pauseCurrentDownload();
    void shutdownCurl();
    void download(int call_number, std::string url, std::string path, FILE* file, curl_off_t progress, std::function<void(int call_number, int response_code, json response)> callback);
    void get(int call_number, std::string url, std::vector<std::string> headers, std::function<void(int call_number, int response_code, json response_json)> callback);
    void post(int call_number, std::string url, std::vector<std::string> headers, std::map<std::string, std::string> data, std::function<void(int call_number, int response_code, json response_json)> callback);
    void put(int call_number, std::string url, std::vector<std::string> headers, std::multimap<std::string, std::string> curlform_copycontents, std::function<void(int call_number, int response_code, json response_json)> callback);
    void postForm(int call_number, std::string url, std::vector<std::string> headers, std::multimap<std::string, std::string> curlform_copycontents, std::map<std::string, std::string> curlform_files, std::function<void(int call_number, int response_code, json response_json)> callback);
    void deleteCall(int call_number, std::string url, std::vector<std::string> headers, std::function<void(int call_number, int response_code, json response_json)> callback);
    void process();
    curl_off_t getProgressIfStored(std::string path);
  }
}

#endif
