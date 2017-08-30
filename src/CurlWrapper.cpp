#include "CurlWrapper.h"

namespace modworks
{
  map<CURL*, GetJsonHandler*> ongoing_calls;
  map<CURL*, DownloadRedirectHandler*> download_redirect_calls;

  int call_count = 0;
  int ongoing_call = 0;

  int getCallCount()
  {
    return call_count;
  }

  int getOngoingCall()
  {
    return ongoing_call;
  }

  void advanceCallCount()
  {
    call_count++;
  }

  void advanceOngoingCall()
  {
    ongoing_call++;
  }

  void lockCall(int call_number)
  {
    while(call_number!=getOngoingCall());
  }

  GetJsonHandler::GetJsonHandler()
  {
    this->response = "";
  }

  DownloadFileHandler::DownloadFileHandler(function< void(int, Mod*) > callback)
  {
    this->callback = callback;
  }

  DownloadRedirectHandler::DownloadRedirectHandler(Mod* mod, string path, string destination_path, function< void(int, Mod*, string) > callback, int call_number)
  {
    this->mod = mod;
    this->path = path;
    this->callback = callback;
    this->destination_path = destination_path;
    this->call_number = call_number;
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

  void getJson(string url, vector<string> headers, function< void(vector<Mod*>) > callback, int call_number)
  {
    writeLogLine("getJsonCall call to " + url, verbose);
    lockCall(call_number);
    CURL *curl;
    CURLcode res;

    struct data config;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    ongoing_calls[curl] = new GetJsonHandler();

    if(curl) {
      struct curl_slist *chunk = NULL;
      for(int i=0;i<(int)headers.size();i++)
        chunk = curl_slist_append(chunk, headers[i].c_str());

      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

      curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, get_json_trace);
      curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

      /* Perform the request, res will get the return code */
      res = curl_easy_perform(curl);
      /* Check for errors */
      if(res != CURLE_OK)
        writeLogLine(string("curl_easy_perform() failed ") + url, verbose);

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
    callback(mods);
    advanceOngoingCall();
    writeLogLine("getJsonCall call to " + url + "finished", verbose);
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

  static int redirect_trace(CURL *handle, curl_infotype type,
               char *data, size_t size,
               void *userp)
  {
    (void)handle; /* prevent compiler warning */
    if(type == CURLINFO_HEADER_IN
      && size > 10 /* "location: " */
      && strncmp(data,"location: ",10) == 0)
    {
      string url = "";
      for(int i = 10; i< (int)size; i++)
      {
        if(data[i]=='\n' || data[i]=='\t' || data[i]==' ' || data[i]==13 /* CR */)
          break;
        url += data[i];
      }

      DownloadRedirectHandler* handler = download_redirect_calls[handle];
      downloadZipFile(handler->mod, url, handler->path, handler->destination_path, handler->callback, handler->call_number);
    }
    return 0;
  }

  size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
  {
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
  }

  void downloadFile(string url, string path)
  {
    writeLogLine("downloadFile call to " + url, verbose);
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

      file = fopen(path.c_str(),"wb");
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

      curl_easy_perform(curl);

      curl_easy_cleanup(curl);

      fclose(file);
    }
    writeLogLine("getJsonCall call to " + url + " finished", verbose);
  }

  void downloadModFile(Mod* mod, string url, string path, function< void(int, Mod*, string) > callback, int call_number)
  {
    writeLogLine("downloadModFile call to " + url, verbose);
    lockCall(call_number);
    downloadFile(url, path);
    callback(1,mod,path);
    advanceOngoingCall();
    writeLogLine("downloadModFile call to " + url + " finished", verbose);
  }

  void downloadRedirect(Mod* mod, string url, string path, string destination_path, function< void(int, Mod*, string) > callback, int call_number)
  {
    writeLogLine("downloadRedirect call to " + url, verbose);
    lockCall(call_number);

    CURL *curl;

    struct data config;

    config.trace_ascii = 1; /* enable ascii tracing */
    //FILE_SIZE = curlGetFileSize(url);
    curl = curl_easy_init();

    if(curl)
    {
      download_redirect_calls[curl] = new DownloadRedirectHandler(mod, path, destination_path, callback, call_number);

      curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, redirect_trace);
      curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

      curl_easy_perform(curl);

      curl_easy_cleanup(curl);
    }
    writeLogLine("downloadRedirect call to " + url + " finished", verbose);
  }

  void downloadZipFile(Mod* mod, string url, string path, string destination, function< void(int, Mod*, string) > callback, int call_number)
  {
    writeLogLine("downloadZipFile call to " + url, verbose);
    lockCall(call_number);
    downloadFile(url, path);
    extract(path, destination);
    callback(1,mod,path);
    advanceOngoingCall();
    writeLogLine("downloadZipFile call to " + url + " finished", verbose);
  }

  void postForm(string url, vector<string> headers, map<string, string> curlform_copycontents, map<string, string> curlform_files)
  {
    writeLogLine(string("postForm call to ") + url, verbose);
    CURL *curl;
    CURLcode res;

    struct curl_httppost *formpost=NULL;
    struct curl_httppost *lastptr=NULL;
    struct curl_slist *headerlist=NULL;
    static const char buf[] = "Expect:";

    curl_global_init(CURL_GLOBAL_ALL);

    for(map<string,string>::iterator i = curlform_files.begin();
          i!=curlform_files.end();
          i++)
    {
      curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, (*i).first.c_str(),
        CURLFORM_FILE, (*i).second.c_str(), CURLFORM_END);
    }

    for(map<string,string>::iterator i = curlform_copycontents.begin();
          i!=curlform_copycontents.end();
          i++)
    {
      curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, (*i).first.c_str(),
        CURLFORM_COPYCONTENTS, (*i).second.c_str(), CURLFORM_END);
    }

    /* Fill in the submit field too, even if this is rarely needed */
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "submit",
                 CURLFORM_COPYCONTENTS, "send",
                 CURLFORM_END);

    curl = curl_easy_init();


    struct curl_slist *chunk = NULL;
    for(int i=0;i<(int)headers.size();i++)
      chunk = curl_slist_append(chunk, headers[i].c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    /* initialize custom header list (stating that Expect: 100-continue is not
       wanted */
    headerlist = curl_slist_append(headerlist, buf);
    if(curl)
    {
      /* what URL that receives this POST */
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
      //if((argc == 2) && (!strcmp(argv[1], "noexpectheader")))
        /* only disable 100-continue header if explicitly requested */
        //curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
      curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

      res = curl_easy_perform(curl);

      if(res != CURLE_OK)
        writeLogLine(string("curl_easy_perform() failed: ") + curl_easy_strerror(res), error);

      curl_easy_cleanup(curl);
      curl_formfree(formpost);
      curl_slist_free_all(headerlist);
    }
    writeLogLine(string("postForm call to ") + url + " finished", verbose);
  }

  int post_trace(CURL *handle, curl_infotype type,
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

  void post(string url, map<string, string> data, function< void(int response) > callback)
  {
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    ongoing_calls[curl] = new GetJsonHandler();

    if(curl)
    {
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

      string str_data = "";
      for(map<string, string>::iterator i = data.begin(); i!=data.end(); i++)
      {
        if(i!=data.begin())
          str_data += "&";
        str_data += (*i).first + "=" + (*i).second;
      }

      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str_data.c_str());
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

      curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, post_trace);

      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

      res = curl_easy_perform(curl);

      if(res != CURLE_OK)
      {
        writeLogLine(string("curl_easy_perform() failed: ") + curl_easy_strerror(res), error);
        callback(-1);
      }

      curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    string json_string = ongoing_calls[curl]->response;

    callback(1);
  }
}
