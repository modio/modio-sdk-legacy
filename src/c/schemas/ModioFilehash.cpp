#include "c/schemas/ModioFilehash.h"

extern "C"
{
  void modioInitFilehash(ModioFilehash* filehash, nlohmann::json filehash_json)
  {
    filehash->md5 = NULL;
    if(modio::hasKey(filehash_json, "md5"))
    {
      std::string md5_str = filehash_json["md5"];
      filehash->md5 = new char[md5_str.size() + 1];
      strcpy(filehash->md5, md5_str.c_str());
    }
  }

  void modioFreeFilehash(ModioFilehash* filehash)
  {
    if(filehash)
    {
      if(filehash->md5)
        delete[] filehash->md5;
    }
  }
}
