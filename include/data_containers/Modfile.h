#ifndef MODWORKS_MODFILE
#define MODWORKS_MODFILE

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modworks
{
  class Modfile
  {
  public:
    Modfile(json image_json);
    int id;
    int mod;
    int member;
    int datevirus;
    int virusstatus;
    int viruspoitive;
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
