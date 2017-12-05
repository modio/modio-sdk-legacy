#ifndef MODIO_MODFILE_H
#define MODIO_MODFILE_H

#include "Globals.h"
#include "extern_c/schemas/ModioModfile.h"
#include "instance/schemas/Filehash.h"

namespace modio
{
  class Modfile
  {
  public:
    u32 id;
    u32 mod_id;
    u32 virus_status;
    u32 virus_positive;
    long date_added;
    long date_scanned;
    long filesize;
    std::string filename;
    std::string version;
    std::string virustotal_hash;
    std::string changelog;
    std::string download_url;
    modio::Filehash filehash;

    void initialize(ModioModfile modfile);
  };
}

#endif
