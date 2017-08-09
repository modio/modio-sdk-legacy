#include <json/json.hpp>
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <map>
#include "Utility.h"

#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERIFICATION

using namespace std;
using json = nlohmann::json;

class GetJsonHandler
{
public:
  string response;
  function< void(json) > callback;

  GetJsonHandler(function< void(json) > callback)
  {
    this->response = "";
    this->callback = callback;
  }
};

int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp);

void getJson(string url, vector<string> headers, function< void(json) > callback);
