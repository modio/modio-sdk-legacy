#include "ModworksSDK.h"

string response;

struct data
{
  char trace_ascii; /* 1 or 0 */
};

string dataToJsonString(char* data, size_t size)
{
  int brackets = 0;
  string response;
  for(int i=0; i<(int)size; i++)
  {
    if(data[i]=='{')
      brackets++;

    if(brackets>0)
    {
      response+=data[i];
    }

    if(data[i]=='}')
      brackets--;
  }
  return response;
}

static int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp)
{
  (void)handle; /* prevent compiler warning */

  if(type == CURLINFO_DATA_IN)
  {
    response = dataToJsonString(data, size);
  }

  return 0;
}

json getJson(string url)
{
  CURL *curl;
  CURLcode res;

  response = "";

  struct data config;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {
    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, "Authorization: Bearer turupawn");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
    curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  json j = json::parse(response);

  return j;
}
