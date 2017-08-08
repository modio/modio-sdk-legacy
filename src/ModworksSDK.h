#include "json/json.hpp"
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>

using namespace std;
using namespace std;
using json = nlohmann::json;

string dataToJsonString(char* data, size_t size);

static int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp);

json getJson(string url);
