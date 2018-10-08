#include "c++/schemas/Modfile.h"

namespace modio
{
void Modfile::initialize(ModioModfile modio_modfile)
{
  this->id = modio_modfile.id;
  this->mod_id = modio_modfile.mod_id;
  this->virus_status = modio_modfile.virus_status;
  this->virus_positive = modio_modfile.virus_positive;
  this->date_added = modio_modfile.date_added;
  this->date_scanned = modio_modfile.date_scanned;
  this->filesize = modio_modfile.filesize;
  if (modio_modfile.filename)
    this->filename = modio_modfile.filename;
  if (modio_modfile.version)
    this->version = modio_modfile.version;
  if (modio_modfile.virustotal_hash)
    this->virustotal_hash = modio_modfile.virustotal_hash;
  if (modio_modfile.changelog)
    this->changelog = modio_modfile.changelog;
  if (modio_modfile.metadata_blob)
    this->metadata_blob = modio_modfile.metadata_blob;
  this->filehash.initialize(modio_modfile.filehash);
  this->download.initialize(modio_modfile.download);
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
