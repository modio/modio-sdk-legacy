#include "data_containers/Modfile.h"

namespace modio
{
  void initModfile(Modfile* modfile, json modfile_json)
  {
    modfile->id = -1;
    if(hasKey(modfile_json, "id"))
      modfile->id = modfile_json["id"];

    modfile->mod = -1;
    if(hasKey(modfile_json, "mod"))
      modfile->mod = modfile_json["mod"];

    modfile->member = NULL;
    if(hasKey(modfile_json, "member"))
    {
      modfile->member = new Member;
      initMember(modfile->member, modfile_json["member"]);
    }

    modfile->datevirus = -1;
    if(hasKey(modfile_json, "datevirus"))
      modfile->datevirus = modfile_json["datevirus"];

    modfile->virusstatus = -1;
    if(hasKey(modfile_json, "virusstatus"))
      modfile->virusstatus = modfile_json["virusstatus"];

    modfile->viruspositive = -1;
    if(hasKey(modfile_json, "viruspositive"))
      modfile->viruspositive = modfile_json["viruspositive"];

    modfile->filesize = -1;
    if(hasKey(modfile_json, "filesize"))
      modfile->filesize = modfile_json["filesize"];

    modfile->filehash = -1;
    if(hasKey(modfile_json, "filehash"))
      modfile->filehash = modfile_json["filehash"];

    modfile->filename = "";
    if(hasKey(modfile_json, "filename"))
      modfile->filename = modfile_json["filename"];

    modfile->version = -1;
    if(hasKey(modfile_json, "version"))
      modfile->version = modfile_json["version"];

    modfile->virustotal = -1;
    if(hasKey(modfile_json, "virustotal"))
      modfile->virustotal = modfile_json["virustotal"];

    modfile->changelog = "";
    if(hasKey(modfile_json, "changelog"))
      modfile->changelog = modfile_json["changelog"];

    modfile->download = "";
    if(hasKey(modfile_json, "download"))
      modfile->download = modfile_json["download"];
  }

  void freeModfile(Modfile* modfile)
  {
    delete modfile;
  }
}
