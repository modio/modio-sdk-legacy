#ifndef MODWORKS_MOD_H
#define MODWORKS_MOD_H

#include <thread>
#include "json/json.hpp"
#include "CurlWrapper.h"

using namespace std;
using json = nlohmann::json;

namespace modworks
{
  struct Logo
  {
    string full;
    string thumbnail;
    string filename;
  };

  struct Modfile
  {
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
    //virustotal ?
    string changelog;
    string download;
  };

  struct Ratings
  {
    int total;
    int positive;
    int negative;
    double weighted;
    int percentage;
    int stars;
    string text;
  };

  struct Tag
  {
    int game;
    int mod;
    int date;
    int member;
    string tag;
  };

  struct Mod
  {
    int id;
    int game;
    int member;
    double price;
    int datereg;
    int dateup;
    Logo logo;
    string homepage;
    string name;
    string nameid;
    string summary;
    string description;
    //metadata ?
    //media ?
    Modfile modfile;
    Ratings ratings;
    Tag tag;
  };

  Mod* jsonToMod(json mod_json);
}

#endif
