#include "wrappers/CurlCallbacks.h"

namespace modio
{
namespace curlwrapper
{

void onJsonRequestFinished(CURL* curl)
{
  JsonResponseHandler* ongoing_call = ongoing_calls[curl];
  u32 response_code;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
  json response_json = modio::toJson(ongoing_call->response);
  writeLogLine("Json request Finished. Response code: " + toString(response_code), MODIO_DEBUGLEVEL_LOG);  
  ongoing_call->callback(ongoing_call->call_number, response_code, response_json);
  call_count++;
  ongoing_calls.erase(curl);
  delete ongoing_call;
}

void onDownloadFinished(CURL* curl)
{
  OngoingDownload* ongoing_download = ongoing_downloads[curl];
  writeLogLine("Download finished.", MODIO_DEBUGLEVEL_LOG);    
  u32 response_code;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
  ongoing_download->callback(ongoing_download->call_number, response_code);
  call_count++;
  ongoing_downloads.erase(curl);  
  delete ongoing_download;
}

void onModDownloadFinished(CURL* curl)
{
  writeLogLine("Download Finished. Mod id: " + toString(current_queued_mod_download->mod_id) + " Url: " + current_queued_mod_download->url, MODIO_DEBUGLEVEL_LOG);
  fclose(current_mod_download_file);
  
  if(current_queued_mod_download->state == MODIO_MOD_DOWNLOADING)
  {
    std::string destination_path_str = modio::getModIODirectory() + "mods/" + modio::toString(current_queued_mod_download->mod_id) + "/";
    writeLogLine("Creating directory...", MODIO_DEBUGLEVEL_LOG);          
    modio::createDirectory(destination_path_str);
    writeLogLine("Extracting...", MODIO_DEBUGLEVEL_LOG);
    modio::minizipwrapper::extract(current_queued_mod_download->path, destination_path_str);
    writeLogLine("Removing temporary file...", MODIO_DEBUGLEVEL_LOG);
    modio::removeFile(current_queued_mod_download->path);

    if (destination_path_str[destination_path_str.size() - 1] != '/')
      destination_path_str += "/";

    modio::createInstalledModJson(current_queued_mod_download->mod.toJson(), destination_path_str + std::string("modio.json"));

    modio::addToInstalledModsJson(current_queued_mod_download->mod.toJson(), destination_path_str);

    mod_download_queue.remove(current_queued_mod_download);

    updateModDownloadQueueFile();
    
    writeLogLine("Finished installing modd", MODIO_DEBUGLEVEL_LOG);

    u32 response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

    if(modio::download_callback)
      modio::download_callback(response_code, current_queued_mod_download->mod.id);
    
    delete current_queued_mod_download;
    current_mod_download_curl_handle = NULL;
    
    if (mod_download_queue.size() > 0)
    {
      downloadMod(mod_download_queue.front());
    }
    
  }else if(current_queued_mod_download->state == MODIO_MOD_PAUSING)
  {
    current_queued_mod_download->state = MODIO_MOD_PAUSED;
  }
  updateModDownloadQueueFile();  
}


}
}