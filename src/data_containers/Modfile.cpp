#include "data_containers/Modfile.h"

extern "C"
{
  void modioInitModfile(ModioModfile* modfile, json modfile_json)
  {
    modfile->id = -1;
    if(modio::hasKey(modfile_json, "id"))
      modfile->id = modfile_json["id"];

    modfile->mod = -1;
    if(modio::hasKey(modfile_json, "mod"))
      modfile->mod = modfile_json["mod"];

    modfile->datevirus = -1;
    if(modio::hasKey(modfile_json, "datevirus"))
      modfile->datevirus = modfile_json["datevirus"];

    modfile->virusstatus = -1;
    if(modio::hasKey(modfile_json, "virusstatus"))
      modfile->virusstatus = modfile_json["virusstatus"];

    modfile->viruspositive = -1;
    if(modio::hasKey(modfile_json, "viruspositive"))
      modfile->viruspositive = modfile_json["viruspositive"];

    modfile->filesize = -1;
    if(modio::hasKey(modfile_json, "filesize"))
      modfile->filesize = modfile_json["filesize"];

    modfile->filehash = NULL;
    if(modio::hasKey(modfile_json, "filehash"))
    {
      string filehash_str = modfile_json["filehash"];
      modfile->filehash = new char[filehash_str.size() + 1];
      strcpy(modfile->filehash, filehash_str.c_str());
    }

    modfile->filename = NULL;
    if(modio::hasKey(modfile_json, "filename"))
    {
      string filename_str = modfile_json["filename"];
      modfile->filename = new char[filename_str.size() + 1];
      strcpy(modfile->filename, filename_str.c_str());
    }

    modfile->version = NULL;
    if(modio::hasKey(modfile_json, "version"))
    {
      string version_str = modfile_json["version"];
      modfile->version = new char[version_str.size() + 1];
      strcpy(modfile->version, version_str.c_str());
    }

    modfile->virustotal = NULL;
    if(modio::hasKey(modfile_json, "virustotal"))
    {
      string virustotal_str = modfile_json["virustotal"];
      modfile->virustotal = new char[virustotal_str.size() + 1];
      strcpy(modfile->virustotal, virustotal_str.c_str());
    }

    modfile->changelog = NULL;
    if(modio::hasKey(modfile_json, "changelog"))
    {
      string changelog_str = modfile_json["changelog"];
      modfile->changelog = new char[changelog_str.size() + 1];
      strcpy(modfile->changelog, changelog_str.c_str());
    }

    modfile->download = NULL;
    if(modio::hasKey(modfile_json, "download"))
    {
      string download_str = modfile_json["download"];
      modfile->download = new char[download_str.size() + 1];
      strcpy(modfile->download, download_str.c_str());
    }
  }

  void modioFreeModfile(ModioModfile* modfile)
  {
    delete modfile;
  }
}
