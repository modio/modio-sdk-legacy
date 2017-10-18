#include "data_containers/Media.h"

extern "C"
{
  void modioInitMedia(ModioMedia* media, json media_json)
  {
    if(modio::hasKey(media_json, "youtube"))
    {
      json youtube_json = media_json["youtube"];
      media->youtube_array = new char*[youtube_json.size()];
      for(int i=0; i<(int)youtube_json.size(); i++)
      {
        string youtube_str = youtube_json[i];
        media->youtube_array[i]= new char[youtube_str.size() + 1];
        strcpy(media->youtube_array[i], youtube_str.c_str());
      }
    }

    if(modio::hasKey(media_json, "sketchfab"))
    {
      json sketchfab_json = media_json["sketchfab"];
      media->sketchfab_array = new char*[sketchfab_json.size()];
      for(int i=0; i<(int)sketchfab_json.size(); i++)
      {
        string sketchfab_str = sketchfab_json[i];
        media->sketchfab_array[i]= new char[sketchfab_str.size() + 1];
        strcpy(media->sketchfab_array[i], sketchfab_str.c_str());
      }
    }

    if(modio::hasKey(media_json, "images"))
    {
      json images_json = media_json["images"];
      media->images_array = new ModioImage*[images_json.size()];
      for(int i=0; i<(int)images_json.size(); i++)
      {
        ModioImage* image = new ModioImage;
        modioInitImage(image, images_json[i]);
        media->images_array[i] = image;
      }
      /*
      json images_json = media_json["images"];
      for(int i=0; i<(int)images_json.size(); i++)
      {
        media->images.push_back(new Image(images_json[i]));
      }
      */
    }
  }

  void modioFreeMedia(ModioMedia* media)
  {
    for(int i=0; i<(int)media->youtube_size; i++)
    {
      delete media->youtube_array[i];
    }
    for(int i=0; i<(int)media->sketchfab_size; i++)
    {
      delete media->sketchfab_array[i];
    }
    for(int i=0; i<(int)media->images_size; i++)
    {
      modioFreeImage(media->images_array[i]);
    }
  }
}
