#ifndef MODWORKS_MOD_H
#define MODWORKS_MOD_H

#include <thread>
#include "json/json.hpp"
#include "CurlWrapper.h"

using namespace std;
using json = nlohmann::json;

namespace modworks
{
  class Image
  {
  public:
    Image(json image_json);
    string full;
    string thumbnail;
    string filename;
  };

  class Media
  {
  public:
    Media(json image_json);
    ~Media();
    vector<string> youtube;
    vector<string> sketchfab;
    vector<Image*> images;
  };

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

  class Ratings
  {
  public:
    Ratings(json ratings_json);
    int total;
    int positive;
    int negative;
    double weighted;
    int percentage;
    int stars;
    string text;
  };

  class Tag
  {
  public:
    Tag(json tag_json);
    int game;
    int mod;
    int date;
    int member;
    string tag;
  };

  class Mod
  {
  public:
    Mod(json mod_json);
    ~Mod();
    int id;
    int game;
    int member;
    double price;
    int datereg;
    int dateup;
    Image* logo;
    string homepage;
    string name;
    string nameid;
    string summary;
    string description;
    string metadata;
    Media* media;
    Modfile* modfile;
    Ratings* ratings;
    Tag* tag;
  };
}

#endif
