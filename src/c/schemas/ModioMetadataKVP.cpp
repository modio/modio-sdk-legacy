#include "c/schemas/ModioMetadataKVP.h"

extern "C"
{
  void modioInitMetadataKVP(ModioMetadataKVP* metadata_kvp, nlohmann::json metadata_kvp_json)
  {
    metadata_kvp->metakey = NULL;
    if(modio::hasKey(metadata_kvp_json, "metakey"))
    {
      std::string metakey_str = metadata_kvp_json["metakey"];
      metadata_kvp->metakey = new char[metakey_str.size() + 1];
      strcpy(metadata_kvp->metakey, metakey_str.c_str());
    }

    metadata_kvp->metavalue = NULL;
    if(modio::hasKey(metadata_kvp_json, "metavalue"))
    {
      std::string metavalue_str = metadata_kvp_json["metavalue"];
      metadata_kvp->metavalue = new char[metavalue_str.size() + 1];
      strcpy(metadata_kvp->metavalue, metavalue_str.c_str());
    }
  }

  void modioFreeMetadataKVP(ModioMetadataKVP* metadata_kvp)
  {
    if(metadata_kvp)
    {
      if(metadata_kvp->metakey)
        delete[] metadata_kvp->metakey;

      if(metadata_kvp->metavalue)
        delete[] metadata_kvp->metavalue;
    }
  }
}
