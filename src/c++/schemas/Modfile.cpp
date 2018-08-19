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
    if(modio_modfile.filename)
      this->filename = modio_modfile.filename;
    if(modio_modfile.version)
      this->version = modio_modfile.version;
    if(modio_modfile.virustotal_hash)
      this->virustotal_hash = modio_modfile.virustotal_hash;
    if(modio_modfile.changelog)
      this->changelog = modio_modfile.changelog;
    if(modio_modfile.metadata_blob)
      this->metadata_blob = modio_modfile.metadata_blob;
    this->filehash.initialize(modio_modfile.filehash);
    this->download.initialize(modio_modfile.download);
  }

  nlohmann::json Modfile::toJson()
  {
    nlohmann::json modfile_json;

    modfile_json["id"] = this->id;
    modfile_json["mod_id"] = this->mod_id;
    modfile_json["virus_status"] = this->virus_status;
    modfile_json["virus_positive"] = this->virus_positive;
    modfile_json["date_added"] = this->date_added;
    modfile_json["date_scanned"] = this->date_scanned;
    modfile_json["filesize"] = this->filesize;
    modfile_json["filename"] = this->filename;
    modfile_json["version"] = this->version;
    modfile_json["virustotal_hash"] = this->virustotal_hash;
    modfile_json["changelog"] = this->changelog;
    modfile_json["metadata_blob"] = this->metadata_blob;
    modfile_json["filehash"] = this->filehash.toJson();
    modfile_json["download"] = this->download.toJson();

    return modfile_json;
  }
}
