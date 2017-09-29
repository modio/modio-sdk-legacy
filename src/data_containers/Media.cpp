#include "data_containers/Media.h"

namespace modworks
{
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

  Media::~Media()
  {
    for(int i=0; i<(int)this->images.size(); i++)
    {
      delete this->images.back();
      this->images.pop_back();
    }
  }
}
