#include "c/schemas/ModioModfile.h"

extern "C"
{
  void modioInitModfile(ModioModfile* modfile, json modfile_json)
  {
    modfile->id = 0;
    if(modio::hasKey(modfile_json, "id"))
      modfile->id = modfile_json["id"];

    modfile->mod_id = 0;
    if(modio::hasKey(modfile_json, "mod_id"))
      modfile->mod_id = modfile_json["mod_id"];

    modfile->virus_status = 0;
    if(modio::hasKey(modfile_json, "virus_status"))
      modfile->virus_status = modfile_json["virus_status"];

    modfile->virus_positive = 0;
    if(modio::hasKey(modfile_json, "virus_positive"))
      modfile->virus_positive = modfile_json["virus_positive"];

    modfile->date_added = 0;
    if(modio::hasKey(modfile_json, "date_added"))
      modfile->date_added = modfile_json["date_added"];

    modfile->date_scanned = 0;
    if(modio::hasKey(modfile_json, "date_scanned"))
      modfile->date_scanned = modfile_json["date_scanned"];

    modfile->filesize = 0;
    if(modio::hasKey(modfile_json, "filesize"))
      modfile->filesize = modfile_json["filesize"];

    modfile->filename = NULL;
    if(modio::hasKey(modfile_json, "filename"))
    {
      std::string filename_str = modfile_json["filename"];
      modfile->filename = new char[filename_str.size() + 1];
      strcpy(modfile->filename, filename_str.c_str());
    }

    modfile->version = NULL;
    if(modio::hasKey(modfile_json, "version"))
    {
      std::string version_str = modfile_json["version"];
      modfile->version = new char[version_str.size() + 1];
      strcpy(modfile->version, version_str.c_str());
    }

    modfile->virustotal_hash = NULL;
    if(modio::hasKey(modfile_json, "virustotal_hash"))
    {
      std::string virustotal_hash_str = modfile_json["virustotal_hash"];
      modfile->virustotal_hash = new char[virustotal_hash_str.size() + 1];
      strcpy(modfile->virustotal_hash, virustotal_hash_str.c_str());
    }

    modfile->changelog = NULL;
    if(modio::hasKey(modfile_json, "changelog"))
    {
      std::string changelog_str = modfile_json["changelog"];
      modfile->changelog = new char[changelog_str.size() + 1];
      strcpy(modfile->changelog, changelog_str.c_str());
    }

    modfile->download_url = NULL;
    if(modio::hasKey(modfile_json, "download_url"))
    {
      std::string download_url_str = modfile_json["download_url"];
      modfile->download_url = new char[download_url_str.size() + 1];
      strcpy(modfile->download_url, download_url_str.c_str());
    }

    json filehash_json;
    if(modio::hasKey(modfile_json, "filehash"))
      filehash_json = modfile_json["filehash"];
    modioInitFilehash(&(modfile->filehash), filehash_json);
  }

  void modioFreeModfile(ModioModfile* modfile)
  {
    if(modfile)
    {
      if(modfile->filename)
        delete[] modfile->filename;
      if(modfile->version)
        delete[] modfile->version;
      if(modfile->virustotal_hash)
        delete[] modfile->virustotal_hash;
      if(modfile->changelog)
        delete[] modfile->changelog;
      if(modfile->download_url)
        delete[] modfile->download_url;

      modioFreeFilehash(&(modfile->filehash));
    }
  }
}
