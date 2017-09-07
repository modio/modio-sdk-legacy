#include "Mod.h"

namespace modworks
{
  Mod::Mod(json mod_json)
  {
    this->id = mod_json["id"];
    this->game = mod_json["game"];
    this->logo_url = mod_json["logo"]["full"];
    this->logo_thumbnail_url = mod_json["logo"]["thumbnail"];
    this->name = mod_json["name"];
    this->summary = mod_json["summary"];
    this->description = mod_json["description"];
    if(mod_json.find("modfile") != mod_json.end() && mod_json["modfile"].find("download") != mod_json["modfile"].end())
    {
      this->download_url = mod_json["modfile"]["download"];
    }
  }

  void Mod::onFileAdded(int call_number, json response)
  {
    add_file_callbacks[call_number]->callback(200,this);
    add_file_callbacks.erase(call_number);
  }

  void Mod::addFile(string directory_path, string version, string changelog, function<void(int, Mod*)> callback)
  {
    modworks::compress(directory_path,".modworks/tmp/modfile.zip");
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    map<string, string> curlform_copycontents;
    curlform_copycontents["version"]=version;
    curlform_copycontents["changelog"]=changelog;
    map<string, string> curlform_files;
    curlform_files["filedata"]=".modworks/tmp/modfile.zip";
    string url = string("https://api.mod.works/v1/games/") + toString(7) + "/mods/" + toString(this->id) + "/files";

    int call_number = getCallCount();
    advanceCallCount();

    add_file_callbacks[call_number] = new AddFileParams;
    add_file_callbacks[call_number]->mod = this;
    add_file_callbacks[call_number]->callback = callback;

    auto on_file_added_ptr = std::bind(&Mod::onFileAdded, *this, placeholders::_1, placeholders::_2);
    std::thread add_file_thread(modworks::postForm, call_number, url, headers, curlform_copycontents, curlform_files, on_file_added_ptr);
    add_file_thread.detach();
  }

  void Mod::onThumbnailDownloaded(int call_number, int status, string url, string path)
  {
    download_thumbnail_callbacks[call_number]->callback(status, this, path);
  }

  void Mod::downloadLogoThumbnail(function< void(int, Mod*, string) > callback)
  {
    writeLogLine("Mod::downloadLogoThumbnail call", verbose);
    string file_path = string(".modworks/images/") + toString(this->game) + "_" + toString(this->id) + "_thumb.png";

    int call_number = getCallCount();
    advanceCallCount();

    download_thumbnail_callbacks[call_number] = new DownloadThumbnailParams;
    download_thumbnail_callbacks[call_number]->mod = this;
    download_thumbnail_callbacks[call_number]->callback = callback;

    auto on_thumbnail_downloaded_ptr = std::bind(&Mod::onThumbnailDownloaded, *this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
    std::thread download_thumbnail_thread(modworks::download, call_number, this->logo_thumbnail_url, file_path, on_thumbnail_downloaded_ptr);
    download_thumbnail_thread.detach();
    writeLogLine("downloadModFile detached", verbose);
  }

  void Mod::onModfileDownloaded(int call_number, int status, string url, string path)
  {
    string destintation_path = download_modfile_callbacks[call_number]->destination_path;
    createDirectory(destintation_path);
    extract(path, destintation_path);
    download_modfile_callbacks[call_number]->callback(status, this, path);
  }

  void Mod::download(string destination_path, function< void(int, Mod*, string) > callback)
  {
    writeLogLine("Mod::download call", verbose);
    string file_path = string(".modworks/tmp/") + toString(this->game) + "_" + toString(this->id) + "_modfile.zip";

    int call_number = getCallCount();
    advanceCallCount();

    //std::thread download_file_thread(downloadRedirect, this, this->download_url + "?shhh=secret", file_path, destination_path, callback, call_count);
    //download_file_thread.detach();

    download_modfile_callbacks[call_number] = new DownloadModfileParams;
    download_modfile_callbacks[call_number]->mod = this;
    download_modfile_callbacks[call_number]->destination_path = destination_path;
    download_modfile_callbacks[call_number]->callback = callback;

    auto on_modifile_downloaded_ptr = std::bind(&Mod::onModfileDownloaded, *this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
    std::thread download_thread(modworks::download, call_number, this->download_url + "?shhh=secret", file_path, on_modifile_downloaded_ptr);
    download_thread.detach();

    writeLogLine("downloadRedirect detached", verbose);
  }
}
