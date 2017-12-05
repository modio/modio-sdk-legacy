#ifndef MODIO_MODIOMODFILE_H
#define MODIO_MODIOMODFILE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "data_containers/ModioUser.h"
#include "data_containers/ModioFilehash.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioModfile
  {
    u32 id;
    u32 mod_id;
    u32 virus_status;
    u32 virus_positive;
    long date_added;
    long date_scanned;
    long filesize;
    char* filename;
    char* version;
    char* virustotal_hash;
    char* changelog;
    char* download_url;
    ModioFilehash filehash;
  };

  void modioInitModfile(ModioModfile* modfile, json modfile_json);
  void modioFreeModfile(ModioModfile* modfile);
}

#endif
