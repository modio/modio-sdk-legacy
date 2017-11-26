#include "instance_data_containers/Modfile.h"

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
    this->filename = modio_modfile.filename;
    this->version = modio_modfile.version;
    this->virustotal = modio_modfile.virustotal;
    this->changelog = modio_modfile.changelog;
    this->download = modio_modfile.download;

    this->filehash.initialize(modio_modfile.filehash);
  }
}
