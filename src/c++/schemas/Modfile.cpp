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
    if(modio_modfile.download_url)
      this->download_url = modio_modfile.download_url;
    this->filehash.initialize(modio_modfile.filehash);
  }
}
