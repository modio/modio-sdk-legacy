#include "data_containers/Media.h"

namespace modio
{
  void initMedia(Media* media, json media_json)
  {
    if(hasKey(media_json, "youtube"))
    {
      json youtube_json = media_json["youtube"];
      for(int i=0; i<(int)youtube_json.size(); i++)
      {
        media->youtube.push_back(youtube_json[i]);
      }
    }

    if(hasKey(media_json, "sketchfab"))
    {
      json sketchfab_json = media_json["sketchfab"];
      for(int i=0; i<(int)sketchfab_json.size(); i++)
      {
        media->sketchfab.push_back(sketchfab_json[i]);
      }
    }

    if(hasKey(media_json, "images"))
    {
      /*
      json images_json = media_json["images"];
      for(int i=0; i<(int)images_json.size(); i++)
      {
        media->images.push_back(new Image(images_json[i]));
      }
      */
    }
  }

  void freeMedia(Media* media)
  {
    for(int i=0; i<(int)media->images.size(); i++)
    {
      freeImage(media->images.back());
      media->images.pop_back();
    }
  }
}
