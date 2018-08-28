#include "c/schemas/ModioMedia.h"

extern "C"
{
  void modioInitMedia(ModioMedia* media, nlohmann::json media_json)
  {
    media->youtube_array = NULL;
    media->youtube_size = 0;
    if(modio::hasKey(media_json, "youtube"))
    {
      nlohmann::json youtube_json = media_json["youtube"];
      media->youtube_size = (u32)youtube_json.size();
      media->youtube_array = new char*[media->youtube_size];
      for(int i=0; i<(int)media->youtube_size; i++)
      {
        std::string youtube_str = youtube_json[i];
        media->youtube_array[i]= new char[media->youtube_size + 1];
        strcpy(media->youtube_array[i], youtube_str.c_str());
      }
    }

    media->sketchfab_array = NULL;
    media->sketchfab_size = 0;
    if(modio::hasKey(media_json, "sketchfab"))
    {
      nlohmann::json sketchfab_json = media_json["sketchfab"];
      media->sketchfab_size = (u32)sketchfab_json.size();
      media->sketchfab_array = new char*[media->sketchfab_size];
      for(int i=0; i<(int)media->sketchfab_size; i++)
      {
        std::string sketchfab_str = sketchfab_json[i];
        media->sketchfab_array[i]= new char[media->sketchfab_size + 1];
        strcpy(media->sketchfab_array[i], sketchfab_str.c_str());
      }
    }

    media->images_array = NULL;
    media->images_size = 0;
    if(modio::hasKey(media_json, "images"))
    {
      nlohmann::json images_json = media_json["images"];
      media->images_size = (u32)images_json.size();
      media->images_array = new ModioImage[media->images_size];
      for(int i=0; i<(int)media->images_size; i++)
      {
        modioInitImage(&(media->images_array[i]), images_json[i]);
      }
    }
  }

  void modioFreeMedia(ModioMedia* media)
  {
    if(media)
    {
      for(int i=0; i<(int)media->youtube_size; i++)
      {
        delete[] media->youtube_array[i];
      }
      if(media->youtube_array)
        delete[] media->youtube_array;

      for(int i=0; i<(int)media->sketchfab_size; i++)
      {
        delete[] media->sketchfab_array[i];
      }
      if(media->sketchfab_array)
        delete[] media->sketchfab_array;

      for(int i=0; i<(int)media->images_size; i++)
      {
        modioFreeImage(&(media->images_array[i]));
      }
      if(media->images_array)
        delete[] media->images_array;
    }
  }
}
