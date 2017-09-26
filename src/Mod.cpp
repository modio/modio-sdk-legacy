#include "Mod.h"

namespace modworks
{
  Image::Image(json image_json)
  {
    this->full = "";
    if(hasKey(image_json, "full"))
      this->full = image_json["full"];

    this->thumbnail = "";
    if(hasKey(image_json, "thumbnail"))
      this->thumbnail = image_json["thumbnail"];

    this->filename = "";
    if(hasKey(image_json, "filename"))
      this->filename = image_json["filename"];
  }

  Media::Media(json media_json)
  {
    if(hasKey(media_json, "youtube"))
    {
      json youtube_json = media_json["youtube"];
      for(int i=0; i<(int)youtube_json.size(); i++)
      {
        this->youtube.push_back(youtube_json[i]);
      }
    }

    if(hasKey(media_json, "sketchfab"))
    {
      json sketchfab_json = media_json["sketchfab"];
      for(int i=0; i<(int)sketchfab_json.size(); i++)
      {
        this->sketchfab.push_back(sketchfab_json[i]);
      }
    }

    if(hasKey(media_json, "images"))
    {
      json images_json = media_json["images"];
      for(int i=0; i<(int)images_json.size(); i++)
      {
        this->images.push_back(new Image(images_json[i]));
      }
    }
  }

  Modfile::Modfile(json modfile_json)
  {
    this->id = -1;
    if(hasKey(modfile_json, "id"))
      this->id = modfile_json["id"];

    this->mod = -1;
    if(hasKey(modfile_json, "mod"))
      this->mod = modfile_json["mod"];

    this->member = -1;
    if(hasKey(modfile_json, "member"))
      this->member = modfile_json["member"];

    this->datevirus = -1;
    if(hasKey(modfile_json, "datevirus"))
      this->datevirus = modfile_json["datevirus"];

    this->virusstatus = -1;
    if(hasKey(modfile_json, "virusstatus"))
      this->virusstatus = modfile_json["virusstatus"];

    this->viruspoitive = -1;
    if(hasKey(modfile_json, "viruspoitive"))
      this->viruspoitive = modfile_json["viruspoitive"];

    this->filesize = -1;
    if(hasKey(modfile_json, "filesize"))
      this->filesize = modfile_json["filesize"];

    this->filehash = -1;
    if(hasKey(modfile_json, "filehash"))
      this->filehash = modfile_json["filehash"];

    this->filename = "";
    if(hasKey(modfile_json, "filename"))
      this->filename = modfile_json["filename"];

    this->version = -1;
    if(hasKey(modfile_json, "version"))
      this->version = modfile_json["version"];

    this->virustotal = -1;
    if(hasKey(modfile_json, "virustotal"))
      this->virustotal = modfile_json["virustotal"];

    this->changelog = "";
    if(hasKey(modfile_json, "changelog"))
      this->changelog = modfile_json["changelog"];

    this->download = "";
    if(hasKey(modfile_json, "download"))
      this->download = modfile_json["download"];
  }

  Ratings::Ratings(json ratings_json)
  {
    this->total = -1;
    if(hasKey(ratings_json, "total"))
      this->total = ratings_json["total"];

    this->positive = -1;
    if(hasKey(ratings_json, "positive"))
      this->positive = ratings_json["positive"];

    this->negative = -1;
    if(hasKey(ratings_json, "negative"))
      this->negative = ratings_json["negative"];

    this->weighted = -1;
    if(hasKey(ratings_json, "weighted"))
      this->weighted = ratings_json["weighted"];

    this->percentage = -1;
    if(hasKey(ratings_json, "percentage"))
      this->percentage = ratings_json["percentage"];

    this->stars = -1;
    if(hasKey(ratings_json, "stars"))
      this->stars = ratings_json["stars"];

    this->text = "";
    if(hasKey(ratings_json, "text"))
      this->text = ratings_json["text"];
  }

  Tag::Tag(json tag_json)
  {
    this->game = -1;
    if(hasKey(tag_json, "game"))
      this->game = tag_json["game"];

    this->mod = -1;
    if(hasKey(tag_json, "mod"))
      this->mod = tag_json["mod"];

    this->date = -1;
    if(hasKey(tag_json, "date"))
      this->date = tag_json["date"];

    this->member = -1;
    if(hasKey(tag_json, "member"))
      this->member = tag_json["member"];

    this->tag = "";
    if(hasKey(tag_json, "tag"))
      this->tag = tag_json["tag"];
  }

  Mod::Mod(json mod_json)
  {
    this->id = -1;
    if(hasKey(mod_json, "id"))
      this->id = mod_json["id"];

    this->game = -1;
    if(hasKey(mod_json, "game"))
      this->game = mod_json["game"];

    this->member = -1;
    if(hasKey(mod_json, "member"))
      this->member = mod_json["member"];

    this->price = -1;
    if(hasKey(mod_json, "price"))
      this->price = mod_json["price"];

    this->datereg = -1;
    if(hasKey(mod_json, "datereg"))
      this->datereg = mod_json["datereg"];

    this->dateup = -1;
    if(hasKey(mod_json, "dateup"))
      this->dateup = mod_json["dateup"];

    this->logo = NULL;
    if(hasKey(mod_json, "logo"))
      this->logo = new Image(mod_json["logo"]);

    this->homepage = "";
    if(hasKey(mod_json, "homepage"))
      this->homepage = mod_json["homepage"];

    this->name = "";
    if(hasKey(mod_json, "name"))
      this->name = mod_json["name"];

    this->nameid = "";
    if(hasKey(mod_json, "nameid"))
      this->nameid = mod_json["nameid"];

    this->summary = "";
    if(hasKey(mod_json, "summary"))
      this->summary = mod_json["summary"];

    this->description = "";
    if(hasKey(mod_json, "description"))
      this->description = mod_json["description"];

    this->metadata = "";
    if(hasKey(mod_json, "metadata"))
      this->metadata = mod_json["metadata"];

    this->media = NULL;
    if(hasKey(mod_json, "media"))
      this->media = new Media(mod_json["media"]);

    this->modfile = NULL;
    if(hasKey(mod_json, "modfile"))
      this->modfile = new Modfile(mod_json["modfile"]);

    this->ratings = NULL;
    if(hasKey(mod_json, "ratings"))
      this->ratings = new Ratings(mod_json["ratings"]);

    this->tag = NULL;
    if(hasKey(mod_json, "tag"))
      this->tag = new Tag(mod_json["tag"]);
  }
}
