#include "wrappers/CurlWrapper.h"

namespace modio
{
namespace curlwrapper
{
void initCurl()
{
  current_mod_download_curl_handle = NULL;
  current_mod_download_slist = NULL;
  current_modfile_upload_slist = NULL;
  current_modfile_upload_httppost = NULL;

  current_download_handle = new CurrentDownloadHandle;
  current_download_handle->path = "";
  current_download_handle->pause_flag = false;
  current_download_handle->curl = NULL;

  curl_multi_handle = curl_multi_init();

  if (curl_global_init(CURL_GLOBAL_ALL) == 0)
    writeLogLine("Curl initialized", MODIO_DEBUGLEVEL_LOG);
  else
    writeLogLine("Error initializing curl", MODIO_DEBUGLEVEL_ERROR);

  resumeModDownloads();
}

void shutdownCurl()
{
  pauseModDownloads();

  ongoing_call = -1;
  call_count = -1;

  curl_multi_cleanup(curl_multi_handle);

  for (auto ongoing_call : ongoing_calls)
  {
    curl_easy_cleanup(ongoing_call.first);
    delete ongoing_call.second;
  }
  ongoing_calls.clear();

  for (auto ongoing_download : ongoing_downloads)
  {
    curl_easy_cleanup(ongoing_download.first);
    delete ongoing_download.second;
  }
  ongoing_downloads.clear();

  for (auto mod_download : mod_download_queue)
  {
    delete mod_download;
  }
  mod_download_queue.clear();

  for (auto modfile_upload : modfile_upload_queue)
  {
    delete modfile_upload;
  }
  modfile_upload_queue.clear();

  if (current_mod_download_file)
    fclose(current_mod_download_file);

  if (current_mod_download_curl_handle)
    curl_easy_cleanup(current_mod_download_curl_handle);

  if (current_modfile_upload_curl_handle)
    curl_easy_cleanup(current_modfile_upload_curl_handle);

  if (current_mod_download_slist)
    curl_slist_free_all(current_mod_download_slist);

  if (current_modfile_upload_slist)
    curl_slist_free_all(current_modfile_upload_slist);

  if (current_modfile_upload_httppost)
    curl_formfree(current_modfile_upload_httppost);

  //current_queued_modfile_upload // ???

  if (current_download_handle)
    delete current_download_handle; // ???
}

u32 getCallNumber()
{
  u32 call_number = call_count;
  call_count++;
  return call_number;
}

void process()
{
  CURLMcode code;
  i32 handle_count;
  code = curl_multi_perform(curl_multi_handle, &handle_count);

  struct CURLMsg *curl_message;

  do
  {
    i32 msgq = 0;
    curl_message = curl_multi_info_read(curl_multi_handle, &msgq);

    if (curl_message && (curl_message->msg == CURLMSG_DONE))
    {
      CURL *curl_handle = curl_message->easy_handle;

      if (ongoing_calls.find(curl_handle) != ongoing_calls.end())
      {
        onJsonRequestFinished(curl_handle);
      }

      if (ongoing_downloads.find(curl_handle) != ongoing_downloads.end())
      {
        onDownloadFinished(curl_handle);
      }

      if (current_mod_download_curl_handle && current_mod_download_curl_handle == curl_handle)
      {
        onModDownloadFinished(curl_handle);
      }

      if (current_modfile_upload_curl_handle && current_modfile_upload_curl_handle == curl_handle)
      {
        onModfileUploadFinished(curl_handle);
      }

      curl_multi_remove_handle(curl_multi_handle, curl_handle);
      curl_easy_cleanup(curl_handle);
    }
    else if (curl_message)
    {
      writeLogLine("Unhandled curl message returned" + modio::toString((u32)curl_message->msg), MODIO_DEBUGLEVEL_ERROR);
    }
  } while (curl_message);
}

void get(u32 call_number, std::string url, std::vector<std::string> headers, std::function<void(u32 call_number, u32 response_code, nlohmann::json response_json)> callback)
{
  writeLogLine("GET: " + url, MODIO_DEBUGLEVEL_LOG);
  CURL *curl;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();

  struct curl_slist *slist = NULL;
  for (u32 i = 0; i < headers.size(); i++)
    slist = curl_slist_append(slist, headers[i].c_str());

  ongoing_calls[curl] = new JsonResponseHandler(call_number, slist, NULL, callback);
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

    url = modio::replaceSubstrings(url, " ", "%20");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    setVerifies(curl);
    setJsonResponseWrite(curl);

    curl_multi_add_handle(curl_multi_handle, curl);
  }
}

void post(u32 call_number, std::string url, std::vector<std::string> headers, std::map<std::string, std::string> data, std::function<void(u32 call_number, u32 response_code, nlohmann::json response_json)> callback)
{
  writeLogLine(std::string("POST: ") + url, MODIO_DEBUGLEVEL_LOG);

  CURL *curl;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  struct curl_slist *slist = NULL;
  for (u32 i = 0; i < headers.size(); i++)
    slist = curl_slist_append(slist, headers[i].c_str());

  ongoing_calls[curl] = new JsonResponseHandler(call_number, slist, NULL, callback);

  if (curl)
  {
    url = modio::replaceSubstrings(url, " ", "%20");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

    std::string str_data = "";
    for (std::map<std::string, std::string>::iterator i = data.begin(); i != data.end(); i++)
    {
      if (i != data.begin())
        str_data += "&";
      str_data += (*i).first + "=" + (*i).second;
    }

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str_data.c_str());

    setVerifies(curl);
    setJsonResponseWrite(curl);

    curl_multi_add_handle(curl_multi_handle, curl);
  }
}

void put(u32 call_number, std::string url, std::vector<std::string> headers, std::multimap<std::string, std::string> curlform_copycontents, std::function<void(u32 call_number, u32 response_code, nlohmann::json response_json)> callback)
{
  writeLogLine(std::string("PUT: ") + url, MODIO_DEBUGLEVEL_LOG);

  CURL *curl;

  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();

  struct curl_slist *slist = NULL;
  for (u32 i = 0; i < headers.size(); i++)
    slist = curl_slist_append(slist, headers[i].c_str());

  ongoing_calls[curl] = new JsonResponseHandler(call_number, slist, NULL, callback);

  if (curl)
  {
    url = modio::replaceSubstrings(url, " ", "%20");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

    std::string str_data = "";
    for (std::map<std::string, std::string>::iterator i = curlform_copycontents.begin(); i != curlform_copycontents.end(); i++)
    {
      if (str_data != "")
        str_data += "&";
      str_data += (*i).first + "=" + (*i).second;
    }

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str_data.c_str());

    setVerifies(curl);
    setJsonResponseWrite(curl);

    curl_multi_add_handle(curl_multi_handle, curl);
  }
}

void postForm(u32 call_number, std::string url, std::vector<std::string> headers, std::multimap<std::string, std::string> curlform_copycontents, std::map<std::string, std::string> curlform_files, std::function<void(u32 call_number, u32 response_code, nlohmann::json response)> callback)
{
	/*
  writeLogLine("POST FORMM: " + url, MODIO_DEBUGLEVEL_LOG);
  CURL *curl;

  curl_global_init(CURL_GLOBAL_ALL);

  curl_mime *form = NULL;
  curl_mimepart *field = NULL;
  struct curl_slist *headerlist = NULL;
  static const char buf[] = "Expect:";

  if(curl)
  {
    form = curl_mime_init(curl);

    for (std::map<std::string, std::string>::iterator i = curlform_files.begin();
        i != curlform_files.end();
        i++)
    {
      field = curl_mime_addpart(form);
      curl_mime_name(field, (*i).first.c_str());
      curl_mime_filedata(field, (*i).second.c_str());
    }

    for (std::map<std::string, std::string>::iterator i = curlform_copycontents.begin();
        i != curlform_copycontents.end();
        i++)
    {
      field = curl_mime_addpart(form);
      curl_mime_name(field, (*i).first.c_str());
      curl_mime_filedata(field, (*i).second.c_str());
    }

    field = curl_mime_addpart(form);
    curl_mime_name(field, "submit");
    curl_mime_data(field, "send", CURL_ZERO_TERMINATED);

    headers.push_back("Content-Type: multipart/form-data");
    struct curl_slist *slist = NULL;
    for (u32 i = 0; i < headers.size(); i++)
    {
      slist = curl_slist_append(slist, headers[i].c_str());
    }

    ongoing_calls[curl] = new JsonResponseHandler(call_number, slist, headerlist, callback);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);

    curl_multi_add_handle(curl_multi_handle, curl);
  }
  */
  writeLogLine("POST FORM: " + url, MODIO_DEBUGLEVEL_LOG);
  CURL *curl;

  struct curl_httppost *formpost = NULL;
  struct curl_httppost *lastptr = NULL;

  curl_global_init(CURL_GLOBAL_ALL);

  for (std::map<std::string, std::string>::iterator i = curlform_files.begin();
       i != curlform_files.end();
       i++)
  {
    curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, (*i).first.c_str(),
                 CURLFORM_FILE, (*i).second.c_str(), CURLFORM_END);
  }

  for (std::map<std::string, std::string>::iterator i = curlform_copycontents.begin();
       i != curlform_copycontents.end();
       i++)
  {
    curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, (*i).first.c_str(),
                 CURLFORM_COPYCONTENTS, (*i).second.c_str(), CURLFORM_END);
  }

  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "submit",
               CURLFORM_COPYCONTENTS, "send",
               CURLFORM_END);

  curl = curl_easy_init();

  headers.push_back("Content-Type: multipart/form-data");
  struct curl_slist *slist = NULL;
  for (u32 i = 0; i < headers.size(); i++)
  {
    slist = curl_slist_append(slist, headers[i].c_str());
  }

  ongoing_calls[curl] = new JsonResponseHandler(call_number, slist, formpost, callback);

  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

    url = modio::replaceSubstrings(url, " ", "%20");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    //setVerifies(curl);
    setJsonResponseWrite(curl);

    //if((argc == 2) && (!strcmp(argv[1], "noexpectheader")))
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, formpost);

    //curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, onModUploadProgress);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

    curl_multi_add_handle(curl_multi_handle, curl);
  }
}

void deleteCall(u32 call_number, std::string url, std::vector<std::string> headers, std::map<std::string, std::string> data, std::function<void(u32 call_number, u32 response_code, nlohmann::json response_json)> callback)
{
  writeLogLine(std::string("DELETE: ") + url, MODIO_DEBUGLEVEL_LOG);
  CURL *curl;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  struct curl_slist *slist = NULL;
  for (u32 i = 0; i < headers.size(); i++)
    slist = curl_slist_append(slist, headers[i].c_str());

  ongoing_calls[curl] = new JsonResponseHandler(call_number, slist, NULL, callback);

  if (curl)
  {
    url = modio::replaceSubstrings(url, " ", "%20");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    headers.push_back("Content-Type: application/x-www-form-urlencoded");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

    std::string str_data = "";
    for (std::map<std::string, std::string>::iterator i = data.begin(); i != data.end(); i++)
    {
      if (i != data.begin())
        str_data += "&";
      str_data += (*i).first + "=" + (*i).second;
    }
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str_data.c_str());

    setVerifies(curl);
    setJsonResponseWrite(curl);

    curl_multi_add_handle(curl_multi_handle, curl);
  }
}

void pauseModDownloads()
{
  //Now
  if (current_queued_mod_download)
  {
    current_queued_mod_download->state = MODIO_MOD_PAUSING;
  }

  //Before
  std::string path = current_download_handle->path;

  if (path != "")
  {
    std::string extension = path.substr(path.length() - 4);

    for (u32 i = 1; i < extension.size(); i++)
      extension[i] = tolower(extension[i]);

    if (extension == ".zip")
    {
      current_download_handle->pause_flag = true;
    }
  }
}

void resumeModDownloads()
{
  updateModDownloadQueue();

  if (mod_download_queue.size() > 0)
  {
    downloadMod(*mod_download_queue.begin());
  }
}

void download(u32 call_number, std::vector<std::string> headers, std::string url, std::string path, FILE *file, std::function<void(u32 call_number, u32 response_code)> callback)
{
  //TODO: Add to download queue
  writeLogLine("DOWNLOAD: " + url, MODIO_DEBUGLEVEL_LOG);
  CURL *curl;
  curl = curl_easy_init();

  current_download_handle->path = path;
  current_download_handle->pause_flag = false;
  current_download_handle->curl = curl;

  struct curl_slist *slist = NULL;
  for (u32 i = 0; i < headers.size(); i++)
    slist = curl_slist_append(slist, headers[i].c_str());

  ongoing_downloads[curl] = new OngoingDownload(call_number, url, slist, callback);

  if (curl)
  {
    url = modio::replaceSubstrings(url, " ", "%20");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

    setVerifies(curl);

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onGetFileData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    curl_multi_add_handle(curl_multi_handle, curl);
  }
}

void onGetInstallMod(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  if (response_code == 200)
  {
    ModioMod modio_mod;
    modioInitMod(&modio_mod, response_json);

    QueuedModDownload *queued_mod_download = NULL;

    for (auto queued_mod_iterator : mod_download_queue)
    {
      if (queued_mod_iterator->mod_id == modio_mod.id)
      {
        queued_mod_download = queued_mod_iterator;
        break;
      }
    }

    if (queued_mod_download == NULL)
    {
      modioFreeMod(&modio_mod);
      writeLogLine("Could not find mod " + modio::toString(modio_mod.id) + "on the download queue. It won't be downloaded.", MODIO_DEBUGLEVEL_LOG);
      return;
    }

    //TODO: Return a download listener error if mod has no modfile
    if (modio_mod.modfile.download.binary_url == NULL)
    {
      modio::writeLogLine("The mod " + modio::toString(modio_mod.id) + " has no modfile to be downloaded", MODIO_DEBUGLEVEL_ERROR);
      if (modio::download_callback)
      {
        modio::download_callback(404, modio_mod.id);
      }

      writeLogLine("Mod download removed from queue. Looking for other mod downloads queued.", MODIO_DEBUGLEVEL_LOG);

      mod_download_queue.remove(queued_mod_download);
      delete queued_mod_download;
      updateModDownloadQueueFile();
      downloadNextQueuedMod();
      modioFreeMod(&modio_mod);
      return;
    }
    else
    {
      queued_mod_download->url = modio_mod.modfile.download.binary_url;
      queued_mod_download->mod.id = modio_mod.id;
      modioFreeMod(&modio_mod);

      writeLogLine("Download started. Mod id: " + toString(queued_mod_download->mod_id) + " Url: " + queued_mod_download->url, MODIO_DEBUGLEVEL_LOG);

      FILE *file;
      curl_off_t progress = (curl_off_t)getFileSize(queued_mod_download->path);
      if (progress != 0)
      {
        file = fopen(queued_mod_download->path.c_str(), "ab");
        writeLogLine("Resuming download from " + toString((u32)progress), MODIO_DEBUGLEVEL_LOG);
      }
      else
      {
        file = fopen(queued_mod_download->path.c_str(), "wb");
      }

      CURL *curl;
      curl = curl_easy_init();

      queued_mod_download->state = MODIO_MOD_STARTING_DOWNLOAD;
      current_mod_download_file = file;
      current_mod_download_curl_handle = curl;

      for (u32 i = 0; i < modio::getHeaders().size(); i++)
        current_mod_download_slist = curl_slist_append(current_mod_download_slist, modio::getHeaders()[i].c_str());

      current_queued_mod_download = queued_mod_download;

      if (curl)
      {
        queued_mod_download->url = modio::replaceSubstrings(queued_mod_download->url, " ", "%20");
        curl_easy_setopt(curl, CURLOPT_URL, queued_mod_download->url.c_str());

        if (progress != 0)
        {
          curl_easy_setopt(curl, CURLOPT_RESUME_FROM_LARGE, progress);
          writeLogLine("Download progress detected. Resuming from " + modio::toString((u32)progress) + " bytes", MODIO_DEBUGLEVEL_LOG);
        }

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, current_mod_download_slist);

        setVerifies(curl);

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onGetFileData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, onModDownloadProgress);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, queued_mod_download);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

        curl_multi_add_handle(curl_multi_handle, curl);
      }
    }
  }
  else
  {
    modio::writeLogLine("Could not download mod. Could not gather mod information.", MODIO_DEBUGLEVEL_ERROR);
  }
}

void downloadMod(QueuedModDownload *queued_mod_download)
{
  u32 call_number = modio::curlwrapper::getCallNumber();

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(queued_mod_download->mod_id) + "?api_key=" + modio::API_KEY;

  modio::curlwrapper::get(call_number, url, modio::getHeaders(), &onGetInstallMod);
}

void queueModDownload(ModioMod &modio_mod)
{
  for (auto &queued_mod_download : mod_download_queue)
  {
    if (queued_mod_download->mod_id == modio_mod.id)
    {
      writeLogLine("Could not queue the mod: " + toString(modio_mod.id) + ". It's already queued.", MODIO_DEBUGLEVEL_WARNING);
      return;
    }
  }

  QueuedModDownload *queued_mod_download = new QueuedModDownload();
  queued_mod_download->state = MODIO_MOD_QUEUED;
  queued_mod_download->mod_id = modio_mod.id;
  queued_mod_download->current_progress = 0;
  queued_mod_download->total_size = 0;
  queued_mod_download->url = "";
  queued_mod_download->mod.initialize(modio_mod);
  queued_mod_download->path = modio::getModIODirectory() + "tmp/" + modio::toString(modio_mod.id) + "_modfile.zip";
  mod_download_queue.push_back(queued_mod_download);

  updateModDownloadQueueFile();

  writeLogLine("Download queued. Mod id: " + toString(modio_mod.id), MODIO_DEBUGLEVEL_LOG);

  if (mod_download_queue.size() == 1)
  {
    downloadMod(queued_mod_download);
  }
}

void uploadModfile(QueuedModfileUpload *queued_modfile_upload)
{
  std::string modfile_path = queued_modfile_upload->modfile_creator.getModioModfileCreator()->path;

  std::string modfile_zip_path = "";

  writeLogLine("Uploading mod: " + toString(queued_modfile_upload->mod_id) + " located at path: " + queued_modfile_upload->path, MODIO_DEBUGLEVEL_LOG);

  if (modio::isDirectory(modfile_path))
  {
    modfile_zip_path = modio::getModIODirectory() + "tmp/upload_" + modio::toString(queued_modfile_upload->mod_id) + "_modfile.zip";
    modio::minizipwrapper::compressDirectory(modfile_path, modfile_zip_path);
  }
  else if (modio::fileExists(modfile_path))
  {
    modfile_zip_path = modfile_path;
  }
  else
  {
    writeLogLine("Could not find the modfile to upload: " + modfile_path, MODIO_DEBUGLEVEL_ERROR);

    modfile_upload_queue.remove(queued_modfile_upload);
    updateModUploadQueueFile();

    if (modio::upload_callback)
    {
      modio::upload_callback(0, queued_modfile_upload->mod_id);
    }

    delete queued_modfile_upload;

    if (modfile_upload_queue.size() > 0)
    {
      uploadModfile(modfile_upload_queue.front());
    }

    return;
  }

  writeLogLine("Upload started", MODIO_DEBUGLEVEL_LOG);

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(queued_modfile_upload->mod_id) + "/files";

  writeLogLine("POST FORM: " + url, MODIO_DEBUGLEVEL_LOG);
  CURL *curl;

  struct curl_httppost *lastptr = NULL;
  static const char buf[] = "Expect:";

  curl_global_init(CURL_GLOBAL_ALL);

  std::multimap<std::string, std::string> curlform_copycontents = modio::convertModfileCreatorToMultimap(queued_modfile_upload->modfile_creator.getModioModfileCreator());

  curl_formadd(&current_modfile_upload_httppost, &lastptr, CURLFORM_COPYNAME, "filedata",
               CURLFORM_FILE, modfile_zip_path.c_str(), CURLFORM_END);

  for (std::map<std::string, std::string>::iterator i = curlform_copycontents.begin();
       i != curlform_copycontents.end();
       i++)
  {
    curl_formadd(&current_modfile_upload_httppost, &lastptr, CURLFORM_COPYNAME, (*i).first.c_str(),
                 CURLFORM_COPYCONTENTS, (*i).second.c_str(), CURLFORM_END);
  }

  curl_formadd(&current_modfile_upload_httppost,
               &lastptr,
               CURLFORM_COPYNAME, "submit",
               CURLFORM_COPYCONTENTS, "send",
               CURLFORM_END);

  curl = curl_easy_init();

  queued_modfile_upload->state = MODIO_MOD_STARTING_UPLOAD;
  current_modfile_upload_curl_handle = curl;
  current_queued_modfile_upload = queued_modfile_upload;

  if (curl)
  {
    for (u32 i = 0; i < modio::getHeaders().size(); i++)
      current_modfile_upload_slist = curl_slist_append(current_modfile_upload_slist, modio::getHeaders()[i].c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, current_modfile_upload_slist);

    url = modio::replaceSubstrings(url, " ", "%20");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    setVerifies(curl);

    curl_easy_setopt(curl, CURLOPT_HTTPPOST, current_modfile_upload_httppost);

    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, onModUploadProgress);
    curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, queued_modfile_upload);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onGetUploadData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, curl);

    curl_multi_add_handle(curl_multi_handle, curl);
  }
}

void queueModfileUpload(u32 mod_id, ModioModfileCreator *modio_modfile_creator)
{
  for (auto &queued_modfile_upload : modfile_upload_queue)
  {
    if (queued_modfile_upload->mod_id == mod_id)
    {
      writeLogLine("Could not queue the mod: " + toString(mod_id) + ". It's already queued.", MODIO_DEBUGLEVEL_WARNING);
      return;
    }
  }

  QueuedModfileUpload *queued_modfile_upload = new QueuedModfileUpload();
  queued_modfile_upload->state = MODIO_MOD_QUEUED;
  queued_modfile_upload->mod_id = mod_id;
  queued_modfile_upload->current_progress = 0;
  queued_modfile_upload->total_size = 0;
  queued_modfile_upload->modfile_creator.initializeFromModioModfileCreator(modio_modfile_creator);
  modfile_upload_queue.push_back(queued_modfile_upload);

  //updateModUploadQueueFile();

  writeLogLine("Upload queued. Mod id: " + toString(mod_id), MODIO_DEBUGLEVEL_LOG);

  if (modfile_upload_queue.size() == 1)
  {
    uploadModfile(queued_modfile_upload);
  }
}
} // namespace curlwrapper
} // namespace modio
