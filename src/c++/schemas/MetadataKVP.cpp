#include "c++/schemas/MetadataKVP.h"

namespace modio
{
void MetadataKVP::initialize(ModioMetadataKVP modio_metadata_kvp)
{
  if (modio_metadata_kvp.metakey)
    this->metakey = modio_metadata_kvp.metakey;

  if (modio_metadata_kvp.metavalue)
    this->metavalue = modio_metadata_kvp.metavalue;
}

nlohmann::json toJson(MetadataKVP &metadata_kvp)
{
  nlohmann::json metadata_kvp_json;

  metadata_kvp_json["metakey"] = metadata_kvp.metakey;
  metadata_kvp_json["metavalue"] = metadata_kvp.metavalue;

  return metadata_kvp_json;
}
} // namespace modio
