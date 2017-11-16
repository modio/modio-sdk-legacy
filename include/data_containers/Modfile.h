#ifndef MODIO_MODFILE_H
#define MODIO_MODFILE_H

#include "dependencies/json/json.hpp"
#include "data_containers/User.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioModfile
  {
    int id;
    int mod;
    int datevirus;
    int virusstatus;
    int viruspositive;
    long filesize;
    char* filehash;
    char* filename;
    char* version;
    char* virustotal;
    char* changelog;
    char* download;
  };

  void modioInitModfile(ModioModfile* modfile, json modfile_json);
  void modioFreeModfile(ModioModfile* modfile);
}

#endif
