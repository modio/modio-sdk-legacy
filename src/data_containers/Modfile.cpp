#include "data_containers/Modfile.h"

namespace modworks
{
  Modfile::Modfile(json modfile_json)
  {
    this->id = -1;
    if(hasKey(modfile_json, "id"))
      this->id = modfile_json["id"];

    this->mod = -1;
    if(hasKey(modfile_json, "mod"))
      this->mod = modfile_json["mod"];

    this->member = -1;
    if(hasKey(modfile_json, "member"))
      this->member = modfile_json["member"];

    this->datevirus = -1;
    if(hasKey(modfile_json, "datevirus"))
      this->datevirus = modfile_json["datevirus"];

    this->virusstatus = -1;
    if(hasKey(modfile_json, "virusstatus"))
      this->virusstatus = modfile_json["virusstatus"];

    this->viruspositive = -1;
    if(hasKey(modfile_json, "viruspositive"))
      this->viruspositive = modfile_json["viruspositive"];

    this->filesize = -1;
    if(hasKey(modfile_json, "filesize"))
      this->filesize = modfile_json["filesize"];

    this->filehash = -1;
    if(hasKey(modfile_json, "filehash"))
      this->filehash = modfile_json["filehash"];

    this->filename = "";
    if(hasKey(modfile_json, "filename"))
      this->filename = modfile_json["filename"];

    this->version = -1;
    if(hasKey(modfile_json, "version"))
      this->version = modfile_json["version"];

    this->virustotal = -1;
    if(hasKey(modfile_json, "virustotal"))
      this->virustotal = modfile_json["virustotal"];

    this->changelog = "";
    if(hasKey(modfile_json, "changelog"))
      this->changelog = modfile_json["changelog"];

    this->download = "";
    if(hasKey(modfile_json, "download"))
      this->download = modfile_json["download"];
  }
}
