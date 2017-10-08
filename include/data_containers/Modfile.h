#ifndef MODIO_MODFILE_H
#define MODIO_MODFILE_H

#include "dependencies/json/json.hpp"
#include "data_containers/Member.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modio
{
  class Modfile
  {
  public:
    Modfile(json image_json);
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
}

#endif
