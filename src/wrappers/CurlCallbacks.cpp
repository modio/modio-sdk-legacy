#include "wrappers/CurlCallbacks.h"

namespace modio
{
namespace curlwrapper
{

void onJsonRequestFinished(CURL *curl)
{
  JsonResponseHandler *ongoing_call = ongoing_calls[curl];
  u32 response_code;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
  nlohmann::json response_json = modio::toJson(ongoing_call->response);

  if (ongoing_call->headers.find("X-Ratelimit-RetryAfter") != ongoing_call->headers.end())
  {
    u32 x_ratelimit_retryafter = atoi((const char *)ongoing_call->headers["X-Ratelimit-RetryAfter"].c_str());
    modio::RETRY_AFTER = modio::getCurrentTime() + x_ratelimit_retryafter;
    modio::writeLogLine("API request limit hit. Could not poll events. Rerying after " + modio::toString(modio::RETRY_AFTER), MODIO_DEBUGLEVEL_WARNING);
  }

  if (ongoing_call->headers.find("X-RateLimit-Remaining") != ongoing_call->headers.end())
  {
    std::string x_rate_limit_remaining = ongoing_call->headers["X-RateLimit-Remaining"];
    if (x_rate_limit_remaining[x_rate_limit_remaining.size() - 1] == '\n')
      x_rate_limit_remaining.pop_back();
    writeLogLine("X-RateLimit-Remaining: " + x_rate_limit_remaining, MODIO_DEBUGLEVEL_LOG);
  }

  writeLogLine("Json request Finished. Response code: " + toString(response_code), MODIO_DEBUGLEVEL_LOG);
  if (response_code >= 400 && response_code <= 599)
  {
    writeLogLine(response_json.dump(), MODIO_DEBUGLEVEL_ERROR);
  }
  ongoing_call->callback(ongoing_call->call_number, response_code, response_json);
  ongoing_calls.erase(curl);
  delete ongoing_call;
  call_count++;
}

void onDownloadFinished(CURL *curl)
{
  OngoingDownload *ongoing_download = ongoing_downloads[curl];

  u32 response_code;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

  if (response_code >= 200 || response_code < 300)
  {
    writeLogLine("Download finished successfully.", MODIO_DEBUGLEVEL_LOG);
  }
  else
  {
    writeLogLine("Response code: " + modio::toString(response_code) + " Could not download form: " + ongoing_download->url, MODIO_DEBUGLEVEL_LOG);
  }

  ongoing_download->callback(ongoing_download->call_number, response_code);
  call_count++;
  ongoing_downloads.erase(curl);
  delete ongoing_download;
}

void onModDownloadFinished(CURL *curl)
{
  fclose(current_mod_download_file);
  current_mod_download_file = NULL;

  if (current_queued_mod_download->state == MODIO_MOD_DOWNLOADING)
  {
    std::string destination_path_str = modio::getModIODirectory() + "mods/" + modio::toString(current_queued_mod_download->mod_id) + "/";
    modio::createDirectory(destination_path_str);
    writeLogLine("Extracting...", MODIO_DEBUGLEVEL_LOG);
    modio::minizipwrapper::extract(current_queued_mod_download->path, destination_path_str);
    writeLogLine("Removing temporary file...", MODIO_DEBUGLEVEL_LOG);
    modio::removeFile(current_queued_mod_download->path);

    destination_path_str = addSlashIfNeeded(destination_path_str);

    modio::writeJson(destination_path_str + std::string("modio.json"), modio::toJson(current_queued_mod_download->mod));

    modio::addToInstalledModsJson(current_queued_mod_download->mod_id,
      destination_path_str,
      current_queued_mod_download->mod.modfile.id,
      current_queued_mod_download->mod.date_updated);

    writeLogLine("Finished installing mod", MODIO_DEBUGLEVEL_LOG);

    u32 response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

    if (response_code >= 200 || response_code < 300)
    {
      writeLogLine("Download finished successfully. Mod id: " + toString(current_queued_mod_download->mod_id) + " Url: " + current_queued_mod_download->url, MODIO_DEBUGLEVEL_LOG);
    }
    else
    {
      writeLogLine("Response code: " + modio::toString(response_code) + " Mod id: " + modio::toString(current_queued_mod_download->mod_id), MODIO_DEBUGLEVEL_ERROR);
    }

    if (modio::download_callback)
      modio::download_callback(response_code, current_queued_mod_download->mod.id);

    modio::curlwrapper::mod_download_queue.remove(current_queued_mod_download);
    delete current_queued_mod_download;
    current_queued_mod_download = NULL;

    current_mod_download_curl_handle = NULL;

    curl_slist_free_all(current_mod_download_slist);
    current_mod_download_slist = NULL;
    
    updateModDownloadQueueFile();
    downloadNextQueuedMod();
  }
  else if (current_queued_mod_download->state == MODIO_MOD_PAUSING)
  {
    modio::writeLogLine("Mod " + modio::toString(current_queued_mod_download->mod_id) + " download paused", MODIO_DEBUGLEVEL_LOG);
    current_queued_mod_download->state = MODIO_MOD_PAUSED;
  }
  else if (current_queued_mod_download->state == MODIO_PRIORITIZING_OTHER_DOWNLOAD)
  {
    modio::writeLogLine("Mod " + modio::toString(current_queued_mod_download->mod_id) + " download paused. Another mod is being prioritized.", MODIO_DEBUGLEVEL_LOG);
    current_queued_mod_download->state = MODIO_MOD_QUEUED;
    updateModDownloadQueue();
    downloadNextQueuedMod();
  }
  updateModDownloadQueueFile();
}

void onModfileUploadFinished(CURL *curl)
{
  writeLogLine("Upload Finished. Mod id: " + toString(current_queued_modfile_upload->mod_id) /*+ " Url: " + current_queued_modfile_upload->url*/, MODIO_DEBUGLEVEL_LOG);

  if (current_queued_modfile_upload->state == MODIO_MOD_UPLOADING)
  {
    modfile_upload_queue.remove(current_queued_modfile_upload);
    updateModUploadQueueFile();

    u32 response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

    if (modio::upload_callback)
    {
      modio::upload_callback(response_code, current_queued_modfile_upload->mod_id);
    }

    delete current_queued_modfile_upload;
    curl_slist_free_all(current_modfile_upload_slist);
    curl_formfree(current_modfile_upload_httppost);

    current_queued_modfile_upload = NULL;
    current_modfile_upload_curl_handle = NULL;
    current_modfile_upload_slist = NULL;
    current_modfile_upload_httppost = NULL;

    if (modfile_upload_queue.size() > 0)
    {
      uploadModfile(modfile_upload_queue.front());
    }
  }
  updateModUploadQueueFile();
}
} // namespace curlwrapper
} // namespace modio