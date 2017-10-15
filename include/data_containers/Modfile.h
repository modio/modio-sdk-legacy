#ifndef MODIO_MODFILE_H
#define MODIO_MODFILE_H

#include "dependencies/json/json.hpp"
#include "data_containers/Member.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct Modfile
  {
    int id;
    int mod;
    Member* member;
    int datevirus;
    int virusstatus;
    int viruspositive;
    long filesize;
    string filehash;
    string filename;
    string version;
    string virustotal;
    string changelog;
    string download;
  };

  void initModfile(Modfile* modfile, json modfile_json);
  void freeModfile(Modfile* modfile);
}

#endif
