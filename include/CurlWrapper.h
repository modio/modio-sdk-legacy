#include <json/json.hpp>
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <map>
#include "Utility.h"
#include "Mod.h"

#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERIFICATION

using namespace std;
using json = nlohmann::json;

class GetJsonHandler
{
public:
  string response;
  function< void(vector<Mod*>) > callback;

  GetJsonHandler(function< void(vector<Mod*>) > callback)
  {
    this->response = "";
    this->callback = callback;
  }
};

int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp);

void getJson(string url, vector<string> headers, function< void(vector<Mod*>) > callback);
