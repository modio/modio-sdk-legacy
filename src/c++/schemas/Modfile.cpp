#include "c++/schemas/Modfile.h"
#include "c/ModioC.h"                      // for ModioModfile
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void Modfile::initialize(ModioModfile modio_modfile)
{
  id = modio_modfile.id;
  mod_id = modio_modfile.mod_id;
  virus_status = modio_modfile.virus_status;
  virus_positive = modio_modfile.virus_positive;
  date_added = modio_modfile.date_added;
  date_scanned = modio_modfile.date_scanned;
  filesize = modio_modfile.filesize;
  if (modio_modfile.filename)
    filename = modio_modfile.filename;
  if (modio_modfile.version)
    version = modio_modfile.version;
  if (modio_modfile.virustotal_hash)
    virustotal_hash = modio_modfile.virustotal_hash;
  if (modio_modfile.changelog)
    changelog = modio_modfile.changelog;
  if (modio_modfile.metadata_blob)
    metadata_blob = modio_modfile.metadata_blob;
  filehash.initialize(modio_modfile.filehash);
  download.initialize(modio_modfile.download);
}

nlohmann::json toJson(Modfile &modfile)
{
  nlohmann::json modfile_json;

  modfile_json["id"] = modfile.id;
  modfile_json["mod_id"] = modfile.mod_id;
  modfile_json["virus_status"] = modfile.virus_status;
  modfile_json["virus_positive"] = modfile.virus_positive;
  modfile_json["date_added"] = modfile.date_added;
  modfile_json["date_scanned"] = modfile.date_scanned;
  modfile_json["filesize"] = modfile.filesize;
  modfile_json["filename"] = modfile.filename;
  modfile_json["version"] = modfile.version;
  modfile_json["virustotal_hash"] = modfile.virustotal_hash;
  modfile_json["changelog"] = modfile.changelog;
  modfile_json["metadata_blob"] = modfile.metadata_blob;
  modfile_json["filehash"] = modio::toJson(modfile.filehash);
  modfile_json["download"] = modio::toJson(modfile.download);

  return modfile_json;
}
} // namespace modio
