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

  this->logo_thumbnail_path = string(".modworks/images/") + toString(this->game) + "_" + toString(this->id) + "_thumb.png";
}

void Mod::downloadLogoThumbnail(function< void(int, Mod*) > callback)
{
  //downloadFile(this->logo_thumbnail_url, this, callback);
  std::thread download_file_thread(downloadFile, this->logo_thumbnail_url, this, callback);
  download_file_thread.detach();
}
