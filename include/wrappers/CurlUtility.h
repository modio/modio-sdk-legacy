#ifndef MODIO_CURL_UTILITY_H
#define MODIO_CURL_UTILITY_H

#include <stdio.h>
#include <iostream>
#include <map>
#include <list>

#include <curl/curl.h>
#include "../Utility.h"
#include "../Globals.h"
#include "MinizipWrapper.h"
#include "CurlProgressFunctions.h"
#include "CurlWriteFunctions.h"
#include "../c++/schemas/QueuedModDownload.h"
#include "../c++/schemas/QueuedModfileUpload.h"
#include "../c/schemas/ModioQueuedModDownload.h"
#include "../c/schemas/ModioQueuedModfileUpload.h"
#include "../ModUtility.h"
#include "CurlWrapper.h"

#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERIFICATION

namespace modio
{
namespace curlwrapper
{

class JsonResponseHandler
{
public:
  u32 call_number;
  std::string response;
  std::map<std::string, std::string> headers;
  struct curl_slist *slist = NULL;
  char *post_fields;
#ifdef MODIO_WINDOWS_DETECTED
  curl_mime *mime_form = NULL;
#elif defined(MODIO_OSX_DETECTED) || defined(MODIO_LINUX_DETECTED)
  struct curl_httppost *formpost = NULL;
#endif
  std::function<void(u32 call_number, u32 response_code, nlohmann::json response_json)> callback;

#ifdef MODIO_WINDOWS_DETECTED
  JsonResponseHandler(u32 call_number, struct curl_slist *slist, char *post_fields, curl_mime *curl_mime, std::function<void(u32 call_number, u32 response_code, nlohmann::json response_json)> callback);
#elif defined(MODIO_OSX_DETECTED) || defined(MODIO_LINUX_DETECTED)
  JsonResponseHandler(u32 call_number, struct curl_slist *slist, char *post_fields, struct curl_httppost *formpost, std::function<void(u32 call_number, u32 response_code, nlohmann::json response_json)> callback);
#endif

  ~JsonResponseHandler();
};

class OngoingDownload
{
public:
  u32 call_number;
  std::string url;
  struct curl_slist *slist = NULL;
  std::function<void(u32 call_number, u32 response_code)> callback;
  OngoingDownload(u32 call_number, std::string url, struct curl_slist *slist, std::function<void(u32 call_number, u32 response_code)> callback);
  ~OngoingDownload();
};

struct CurrentDownloadHandle
{
  CURL *curl;
  std::string path;
  bool pause_flag;
};

extern CURLM *curl_multi_handle;

extern std::map<CURL *, JsonResponseHandler *> ongoing_calls;
extern std::map<CURL *, OngoingDownload *> ongoing_downloads;

extern std::list<QueuedModDownload *> mod_download_queue;
extern std::list<QueuedModfileUpload *> modfile_upload_queue;

extern FILE *current_mod_download_file;

extern CURL *current_mod_download_curl_handle;
extern CURL *current_modfile_upload_curl_handle;

extern struct curl_slist *current_mod_download_slist;
extern struct curl_slist *current_modfile_upload_slist;
extern struct curl_httppost *current_modfile_upload_httppost;

extern QueuedModDownload *current_queued_mod_download;
extern QueuedModfileUpload *current_queued_modfile_upload;
extern CurrentDownloadHandle *current_download_handle;

extern u32 call_count;
extern u32 ongoing_call;

std::list<QueuedModDownload *> getModDownloadQueue();
std::list<QueuedModfileUpload *> getModfileUploadQueue();

void updateModDownloadQueue();
void updateModDownloadQueueFile();
void updateModUploadQueueFile();
void prioritizeModDownload(u32 mod_id);
void downloadNextQueuedMod();

void setHeaders(std::vector<std::string> headers, CURL *curl);
void setVerifies(CURL *curl);
void setJsonResponseWrite(CURL *curl);
std::string mapDataToUrlString(std::map<std::string, std::string> data);
std::string multimapDataToUrlString(std::multimap<std::string, std::string> data);
} // namespace curlwrapper
} // namespace modio

#endif
