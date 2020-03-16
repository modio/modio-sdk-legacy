#include "c/schemas/ModioFilehash.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDownload

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

  void modioInitFilehashCpp(ModioFilehash* modio_filehash, modio::Filehash* filehash)
  {
    modio_filehash->md5 = new char[filehash->md5.size() + 1];
    strcpy(modio_filehash->md5, filehash->md5.c_str());
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
