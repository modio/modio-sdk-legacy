#include "wrappers/CurlUtility.h"

namespace modio
{
namespace curlwrapper
{
CURLM *g_curl_multi_handle;
u32 g_call_count;
u32 g_ongoing_call;

std::map<CURL *, JsonResponseHandler *> g_ongoing_calls;
std::map<CURL *, OngoingDownload *> g_ongoing_downloads;
std::list<QueuedModDownload *> g_mod_download_queue;
std::list<QueuedModfileUpload *> g_modfile_upload_queue;

CurrentModDownload* g_current_mod_download;
CurrentModfileUpload* g_current_modfile_upload;

std::list<QueuedModDownload *> getModDownloadQueue()
{
  return g_mod_download_queue;
}

std::list<QueuedModfileUpload *> getModfileUploadQueue()
{
  return g_modfile_upload_queue;
}

#ifdef MODIO_WINDOWS_DETECTED
JsonResponseHandler::JsonResponseHandler(u32 call_number_, struct curl_slist *slist_, char *post_fields_, curl_mime *mime_form_, std::function<void(u32 call_number, u32 response_code, nlohmann::json response_json)> callback_)
  : call_number(call_number_), response(""), slist(slist_), post_fields(post_fields_), mime_form(mime_form_), callback(callback_)
{
}
#elif defined(MODIO_OSX_DETECTED) || defined(MODIO_LINUX_DETECTED)
JsonResponseHandler::JsonResponseHandler(u32 call_number_, struct curl_slist *slist_, char *post_fields_, struct curl_httppost *formpost_, std::function<void(u32 call_number, u32 response_code, nlohmann::json response_json)> callback_)
  : call_number(call_number_), response(""), slist(slist_), post_fields(post_fields_), formpost(formpost_), callback(callback_)
{
}
#endif

JsonResponseHandler::~JsonResponseHandler()
{
  curl_slist_free_all(slist);
  if (post_fields)
    delete[] post_fields;
#ifdef MODIO_WINDOWS_DETECTED
  curl_mime_free(mime_form);
#elif defined(MODIO_OSX_DETECTED) || defined(MODIO_LINUX_DETECTED)
  curl_formfree(formpost);
#endif
}

CurrentModDownload::CurrentModDownload()
{
  queued_mod_download = NULL;
  curl_handle = NULL;
  slist = NULL;
  file = NULL;
}

CurrentModDownload::~CurrentModDownload()
{
  if(slist)
    curl_slist_free_all(slist);
  if (file)
    fclose(file);
}

CurrentModfileUpload::CurrentModfileUpload()
{
  queued_modfile_upload = NULL;
  curl_handle = NULL;
  slist = NULL;
  httppost = NULL;
}

CurrentModfileUpload::~CurrentModfileUpload()
{
  if(slist)
    curl_slist_free_all(slist);
  if (httppost)
    curl_formfree(httppost);
}

OngoingDownload::OngoingDownload(u32 call_number_, std::string url_, struct curl_slist *slist_, std::function<void(u32 call_number, u32 response_code)> callback_)
  : call_number(call_number_), url(url_), slist(slist_), callback(callback_)
{
}

OngoingDownload::~OngoingDownload()
{
  curl_slist_free_all(slist);
}

void updateModDownloadQueue()
{
  nlohmann::json mod_download_queue_json = openJson(modio::getModIODirectory() + "mod_download_queue.json");

  for (auto &queued_mod_download : g_mod_download_queue)
  {
    delete queued_mod_download;
  }
  g_mod_download_queue.clear();

  for (auto &queued_mod_download_json : mod_download_queue_json)
  {
    ModioQueuedModDownload modio_queued_mod_download;
    modioInitQueuedModDownload(&modio_queued_mod_download, queued_mod_download_json);
    QueuedModDownload *queued_mod_download = new QueuedModDownload();
    queued_mod_download->initialize(modio_queued_mod_download);
    g_mod_download_queue.push_back(queued_mod_download);
    modioFreeQueuedModDownload(&modio_queued_mod_download);
  }
}

void updateModDownloadQueueFile()
{
  modio::writeLogLine("Updating mod download queue file...", MODIO_DEBUGLEVEL_LOG);
  nlohmann::json mod_download_queue_json;
  for (auto &queued_mod_download : g_mod_download_queue)
  {
    mod_download_queue_json.push_back(modio::toJson(*queued_mod_download));
  }
  writeJson(modio::getModIODirectory() + "mod_download_queue.json", mod_download_queue_json);
  modio::writeLogLine("Finished updating mod download queue file", MODIO_DEBUGLEVEL_LOG);
}

void updateModUploadQueueFile()
{
  nlohmann::json mod_upload_queue_json;
  for (auto &queued_mod_upload : g_modfile_upload_queue)
  {
    mod_upload_queue_json.push_back(modio::toJson(*queued_mod_upload));
  }
  writeJson(modio::getModIODirectory() + "mod_upload_queue.json", mod_upload_queue_json);
}

void prioritizeModDownload(u32 mod_id)
{
  nlohmann::json result_json;
  nlohmann::json mod_download_queue_json = openJson(modio::getModIODirectory() + "mod_download_queue.json");

  for (auto &queued_mod_download_json : mod_download_queue_json)
  {
    if (modio::hasKey(queued_mod_download_json, "mod")
        && modio::hasKey(queued_mod_download_json["mod"], "id")
        && queued_mod_download_json["mod"]["id"] == mod_id)
    {
      result_json.push_back(queued_mod_download_json);
    }
  }

  for (auto &queued_mod_download_json : mod_download_queue_json)
  {
    if (modio::hasKey(queued_mod_download_json, "mod")
        && modio::hasKey(queued_mod_download_json["mod"], "id")
        && queued_mod_download_json["mod"]["id"] != mod_id)
    {
      result_json.push_back(queued_mod_download_json);
    }
  }

  writeJson(modio::getModIODirectory() + "mod_download_queue.json", result_json);

  if (g_current_mod_download->queued_mod_download)
    g_current_mod_download->queued_mod_download->state = MODIO_PRIORITIZING_OTHER_DOWNLOAD;
}

void downloadNextQueuedMod()
{
  if (g_mod_download_queue.size() > 0)
  {
    downloadMod(g_mod_download_queue.front());
  }
}

void uploadNextQueuedModfile()
{
  if (g_modfile_upload_queue.size() > 0)
  {
    uploadModfile(g_modfile_upload_queue.front());
  }
}

void setHeaders(std::vector<std::string> headers, CURL *curl)
{
  struct curl_slist *chunk = NULL;
  for (u32 i = 0; i < headers.size(); i++)
    chunk = curl_slist_append(chunk, headers[i].c_str());

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
}

void setVerifies(CURL *curl)
{
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
}

void setJsonResponseWrite(CURL *curl)
{
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onGetJsonData);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, curl);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, &headerCallback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, curl);
}

std::string mapDataToUrlString(std::map<std::string, std::string> data)
{
  std::string url_string = "";
  for (std::map<std::string, std::string>::iterator i = data.begin(); i != data.end(); i++)
  {
    if (url_string != "")
      url_string += "&";
    url_string += (*i).first + "=" + (*i).second;
  }
  return url_string;
}

std::string multimapDataToUrlString(std::multimap<std::string, std::string> data)
{
  std::string url_string = "";
  for (std::map<std::string, std::string>::iterator i = data.begin(); i != data.end(); i++)
  {
    if (url_string != "")
      url_string += "&";
    url_string += (*i).first + "=" + (*i).second;
  }
  return url_string;
}

void setupCurrentModDownload(CurrentModDownload *current_mod_download, u32 mod_id)
{
  for (auto queued_mod_iterator : g_mod_download_queue)
  {
    if (queued_mod_iterator->mod_id == mod_id)
    {
      current_mod_download->queued_mod_download = queued_mod_iterator;
      break;
    }
  }
}

void handleOnGetDownloadModError(ModioMod* modio_mod)
{
  if (modio::download_callback)
  {
    modio::download_callback(404, modio_mod->id);
  }

  writeLogLine("Mod download removed from queue. Looking for other mod downloads queued.", MODIO_DEBUGLEVEL_LOG);

  g_mod_download_queue.remove(g_current_mod_download->queued_mod_download);
  delete g_current_mod_download->queued_mod_download;
  updateModDownloadQueueFile();
  downloadNextQueuedMod();
  modioFreeMod(modio_mod);
}

std::string dataURLEncode(std::string data)
{
  char *output = curl_easy_escape(NULL, data.c_str(), (int)data.length());
  if(output) {
    data = std::string(output);
    curl_free(output);
  }
  return data;
}

} // namespace curlwrapper
} // namespace modio
