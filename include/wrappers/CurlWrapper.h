#ifndef MODIO_CURL_WRAPPER_H
#define MODIO_CURL_WRAPPER_H

#define CURL_STATICLIB

#include <stdio.h>
#include <iostream>
#include <map>

#include "dependencies/json/json.hpp"
#include "dependencies/curl/curl.h"
#include "Utility.h"
#include "wrappers/MinizipWrapper.h"

#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERIFICATION

using json = nlohmann::json;

namespace modio
{
  namespace curlwrapper
  {
    void initCurl();
    u32 getCallCount();
    u32 getOngoingCall();
    void advanceCallCount();
    void advanceOngoingCall();
    void cleanCallQueue();

    class JsonResponseHandler
    {
    public:
      std::string response;
      u32 call_number;
      std::function<void(u32 call_number, u32 response_code, json response_json)> callback;
      JsonResponseHandler(u32 call_number, std::function<void(u32 call_number, u32 response_code, json response_json)> callback);
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
    void download(u32 call_number, std::string url, std::string path, FILE* file, curl_off_t progress, std::function<void(u32 call_number, u32 response_code, json response)> callback);
    void get(u32 call_number, std::string url, std::vector<std::string> headers, std::function<void(u32 call_number, u32 response_code, json response_json)> callback);
    void post(u32 call_number, std::string url, std::vector<std::string> headers, std::map<std::string, std::string> data, std::function<void(u32 call_number, u32 response_code, json response_json)> callback);
    void put(u32 call_number, std::string url, std::vector<std::string> headers, std::multimap<std::string, std::string> curlform_copycontents, std::function<void(u32 call_number, u32 response_code, json response_json)> callback);
    void postForm(u32 call_number, std::string url, std::vector<std::string> headers, std::multimap<std::string, std::string> curlform_copycontents, std::map<std::string, std::string> curlform_files, std::function<void(u32 call_number, u32 response_code, json response_json)> callback);
    void deleteCall(u32 call_number, std::string url, std::vector<std::string> headers, std::function<void(u32 call_number, u32 response_code, json response_json)> callback);
    void process();
    curl_off_t getProgressIfStored(std::string path);
  }
}

#endif
