#include "c/schemas/ModioAvatar.h"
#include <string.h>                 // for strcpy, NULL
#include <string>                   // for string
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioAvatar

extern "C"
{
  void modioInitAvatar(ModioAvatar* avatar, nlohmann::json avatar_json)
  {
    avatar->filename = NULL;
    if(modio::hasKey(avatar_json, "filename"))
    {
      std::string filename_str = avatar_json["filename"];
      avatar->filename = new char[filename_str.size() + 1];
      strcpy(avatar->filename, filename_str.c_str());
    }

    avatar->original = NULL;
    if(modio::hasKey(avatar_json, "original"))
    {
      std::string original_str = avatar_json["original"];
      avatar->original = new char[original_str.size() + 1];
      strcpy(avatar->original, original_str.c_str());
    }

    avatar->thumb_50x50 = NULL;
    if(modio::hasKey(avatar_json, "thumb_50x50"))
    {
      std::string thumb_50x50_str = avatar_json["thumb_50x50"];
      avatar->thumb_50x50 = new char[thumb_50x50_str.size() + 1];
      strcpy(avatar->thumb_50x50, thumb_50x50_str.c_str());
    }

    avatar->thumb_100x100 = NULL;
    if(modio::hasKey(avatar_json, "thumb_100x100"))
    {
      std::string thumb_100x100_str = avatar_json["thumb_100x100"];
      avatar->thumb_100x100 = new char[thumb_100x100_str.size() + 1];
      strcpy(avatar->thumb_100x100, thumb_100x100_str.c_str());
    }
  }

  void modioInitAvatarCpp(ModioAvatar* modio_avatar, modio::Avatar* avatar)
  {
    modio_avatar->filename = new char[avatar->filename.size() + 1];
    strcpy(modio_avatar->filename, avatar->filename.c_str());

    modio_avatar->original = new char[avatar->original.size() + 1];
    strcpy(modio_avatar->original, avatar->original.c_str());

    modio_avatar->thumb_50x50 = new char[avatar->thumb_50x50.size() + 1];
    strcpy(modio_avatar->thumb_50x50, avatar->thumb_50x50.c_str());

    modio_avatar->thumb_100x100 = new char[avatar->thumb_100x100.size() + 1];
    strcpy(modio_avatar->thumb_100x100, avatar->thumb_100x100.c_str());
  }

  void modioFreeAvatar(ModioAvatar* avatar)
  {
    if(avatar)
    {
      if(avatar->filename)
        delete[] avatar->filename;

      if(avatar->original)
        delete[] avatar->original;

      if(avatar->thumb_50x50)
        delete[] avatar->thumb_50x50;

      if(avatar->thumb_100x100)
        delete[] avatar->thumb_100x100;
    }
  }
}
