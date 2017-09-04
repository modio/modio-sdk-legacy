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

  void Mod::onFileAdded(json response)
  {
    cout<<"File added!"<<endl;
  }

  void Mod::addFile(string directory_path, string version, string changelog)
  {
    modworks::compress(directory_path,"test.zip");
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    map<string, string> curlform_copycontents;
    curlform_copycontents["version"]=version;
    curlform_copycontents["changelog"]=changelog;
    map<string, string> curlform_files;
    curlform_files["filedata"]="test.zip";
    string url = string("https://api.mod.works/v1/games/") + toString(7) + "/mods/" + toString(this->id) + "/files";

    auto on_file_added_ptr = std::bind(&Mod::onFileAdded, *this, placeholders::_1);
    modworks::postForm(url, headers, curlform_copycontents, curlform_files, on_file_added_ptr);
  }

  void Mod::downloadLogoThumbnail(function< void(int, Mod*, string) > callback)
  {
    writeLogLine("Mod::downloadLogoThumbnail call", verbose);
    string file_path = string(".modworks/images/") + toString(this->game) + "_" + toString(this->id) + "_thumb.png";

    int call_count = getCallCount();
    advanceCallCount();

    std::thread download_file_thread(downloadModFile, this, this->logo_thumbnail_url, file_path, callback, call_count);
    download_file_thread.detach();
    writeLogLine("downloadModFile detached", verbose);
  }

  void Mod::download(string destination_path, function< void(int, Mod*, string) > callback)
  {
    writeLogLine("Mod::download call", verbose);
    string file_path = string(".modworks/tmp/") + toString(this->game) + "_" + toString(this->id) + "_modfile.zip";

    int call_count = getCallCount();
    advanceCallCount();

    std::thread download_file_thread(downloadRedirect, this, this->download_url + "?shhh=secret", file_path, destination_path, callback, call_count);
    download_file_thread.detach();
    writeLogLine("downloadRedirect detached", verbose);
  }
}
