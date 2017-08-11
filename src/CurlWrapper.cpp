#include "CurlWrapper.h"

map<CURL*, GetJsonHandler*> ongoing_calls;

GetJsonHandler::GetJsonHandler(function< void(vector<Mod*>) > callback)
{
  this->response = "";
  this->callback = callback;
}

DownloadFileHandler::DownloadFileHandler(function< void(int) > callback)
{
  this->callback = callback;
}

struct data
{
  char trace_ascii; /* 1 or 0 */
};

int get_json_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp)
{
  (void)handle; /* prevent compiler warning */

  if(type == CURLINFO_DATA_IN)
  {
    ongoing_calls[handle]->response = dataToJsonString(data, size);
  }

  return 0;
}

void getJson(string url, vector<string> headers, function< void(vector<Mod*>) > callback)
{
  CURL *curl;
  CURLcode res;

  struct data config;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();

  ongoing_calls[curl] = new GetJsonHandler(callback);

  if(curl) {
    struct curl_slist *chunk = NULL;
    for(int i=0;i<(int)headers.size();i++)
      chunk = curl_slist_append(chunk, headers[i].c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, get_json_trace);
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
  string json_string = ongoing_calls[curl]->response;
  json json_response = json::parse(json_string);

  vector<Mod*> mods;
  for(int i=0;i<(int)json_response["data"].size();i++)
  {
    Mod* mod = new Mod(json_response["data"][i]);
    mods.push_back(mod);
  }
  ongoing_calls[curl]->callback(mods);
}

double curlGetFileSize(string url)
{
  CURL *curl;
  curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_HEADER, 1);
  curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_perform(curl);

  double result;
  curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &result);
  curl_easy_cleanup(curl);

  return result;
}

static int download_file_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp)
{
  (void)handle; /* prevent compiler warning */

  if(type == CURLINFO_DATA_IN)
  {
    //BYTES_DOWNLOADED+=size;
  }
  return 0;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

void downloadFile(string url, string download_path, function< void(int) > callback)
{
  CURL *curl;
  FILE *file;

  struct data config;

  config.trace_ascii = 1; /* enable ascii tracing */
  //FILE_SIZE = curlGetFileSize(url);
  curl = curl_easy_init();
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, download_file_trace);
    curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    file = fopen(download_path.c_str(),"wb");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    fclose(file);
  }
  callback(1);
}
