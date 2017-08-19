#include "Mod.h"

Mod::Mod(json mod_json)
{
  this->id = mod_json["id"];
  this->game = mod_json["game"];
  this->logo_url = mod_json["logo"]["full"];
  this->logo_thumbnail_url = mod_json["logo"]["thumbnail"];
  this->name = mod_json["name"];
  this->summary = mod_json["summary"];
  this->description = mod_json["description"];
  this->download_url = mod_json["modfile"]["download"];
  //https:\/\/mod.works\/mods\/file\/12\/dc5337bed727254fe0218bd7712d961a?shhh=secret
}

void Mod::downloadLogoThumbnail(function< void(int, Mod*, string) > callback)
{
  string file_path = string(".modworks/images/") + toString(this->game) + "_" + toString(this->id) + "_thumb.png";

  int call_count = getCallCount();
  advanceCallCount();

  std::thread download_file_thread(downloadModFile, this, this->logo_thumbnail_url, file_path, callback, call_count);
  download_file_thread.detach();
}

void Mod::download(string destination_path, function< void(int, Mod*, string) > callback)
{
  string file_path = string(".modworks/tmp/") + toString(this->game) + "_" + toString(this->id) + "_modfile.zip";

  int call_count = getCallCount();
  advanceCallCount();

  std::thread download_file_thread(downloadRedirect, this, this->download_url + "?shhh=secret", file_path, destination_path, callback, call_count);
  download_file_thread.detach();
}
