#include <json/json.hpp>
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include "Utility.h"

#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERIFICATION

using namespace std;
using namespace std;
using json = nlohmann::json;

int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp);

json getJson(string url, vector<string>);
