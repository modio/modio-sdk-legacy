#include "c/creators/ModioModEditor.h"

extern "C"
{
  void modioInitModEditor(ModioModEditor* mod_editor)
  {
    mod_editor->visible = NULL;
    mod_editor->status = NULL;
    mod_editor->maturity_option = NULL;
    mod_editor->name = NULL;
    mod_editor->name_id = NULL;
    mod_editor->summary = NULL;
    mod_editor->description = NULL;
    mod_editor->homepage_url = NULL;
    mod_editor->modfile = NULL;
    mod_editor->metadata_blob = NULL;
    mod_editor->modfile = NULL;
  }

  void modioSetModEditorVisible(ModioModEditor* mod_editor, u32 visible)
  {
    if(mod_editor->visible)
      delete[] mod_editor->visible;

    mod_editor->visible = new char[modio::toString(visible).size() + 1];
    strcpy(mod_editor->visible, modio::toString(visible).c_str());
  }

  void modioSetModEditorStatus(ModioModEditor* mod_editor, u32 status)
  {
    if(mod_editor->status)
      delete[] mod_editor->status;

    mod_editor->status = new char[modio::toString(status).size() + 1];
    strcpy(mod_editor->status, modio::toString(status).c_str());
  }

  void modioSetModEditorMaturityOption(ModioModEditor* mod_editor, u32 maturity_option)
  {
    if(mod_editor->maturity_option)
      delete[] mod_editor->maturity_option;

    mod_editor->maturity_option = new char[modio::toString(maturity_option).size() + 1];
    strcpy(mod_editor->maturity_option, modio::toString(maturity_option).c_str());
  }

  void modioSetModEditorName(ModioModEditor* mod_editor, char const* name)
  {
    if(mod_editor->name)
      delete[] mod_editor->name;

    mod_editor->name = new char[strlen(name) + 1];
    strcpy(mod_editor->name, name);
  }

  void modioSetModEditorNameid(ModioModEditor* mod_editor, char const* name_id)
  {
    if(mod_editor->name_id)
      delete[] mod_editor->name_id;

    mod_editor->name_id = new char[strlen(name_id) + 1];
    strcpy(mod_editor->name_id, name_id);
  }

  void modioSetModEditorSummary(ModioModEditor* mod_editor, char const* summary)
  {
    if(mod_editor->summary)
      delete[] mod_editor->summary;

    mod_editor->summary = new char[strlen(summary) + 1];
    strcpy(mod_editor->summary, summary);
  }

  void modioSetModEditorDescription(ModioModEditor* mod_editor, char const* description)
  {
    if(mod_editor->description)
      delete[] mod_editor->description;

    mod_editor->description = new char[strlen(description) + 1];
    strcpy(mod_editor->description, description);
  }

  void modioSetModEditorHomepageURL(ModioModEditor* mod_editor, char const* homepage_url)
  {
    if(mod_editor->homepage_url)
      delete[] mod_editor->homepage_url;

    mod_editor->homepage_url = new char[strlen(homepage_url) + 1];
    strcpy(mod_editor->homepage_url, homepage_url);
  }

  void modioSetModEditorModfile(ModioModEditor* mod_editor, u32 modfile)
  {
    if(mod_editor->modfile)
      delete[] mod_editor->modfile;

    mod_editor->modfile = new char[modio::toString(modfile).size() + 1];
    strcpy(mod_editor->modfile, modio::toString(modfile).c_str());
  }

  void modioSetModEditorMetadataBlob(ModioModEditor* mod_editor, char const* metadata_blob)
  {
    if(mod_editor->metadata_blob)
      delete[] mod_editor->metadata_blob;

    mod_editor->metadata_blob = new char[strlen(metadata_blob) + 1];
    strcpy(mod_editor->metadata_blob, metadata_blob);
  }

  void modioFreeModEditor(ModioModEditor* mod_editor)
  {
    if(mod_editor->visible)
      delete[] mod_editor->visible;
    if(mod_editor->status)
      delete[] mod_editor->status;
    if(mod_editor->maturity_option)
      delete[] mod_editor->maturity_option;
    if(mod_editor->name)
      delete[] mod_editor->name;
    if(mod_editor->name_id)
      delete[] mod_editor->name_id;
    if(mod_editor->summary)
      delete[] mod_editor->summary;
    if(mod_editor->description)
      delete[] mod_editor->description;
    if(mod_editor->homepage_url)
      delete[] mod_editor->homepage_url;
    if(mod_editor->modfile)
      delete[] mod_editor->modfile;
    if(mod_editor->metadata_blob)
      delete[] mod_editor->metadata_blob;
  }
}

namespace modio
{
  std::multimap<std::string, std::string> getModEditorCurlFormCopyContentsParams(ModioModEditor* mod_editor)
  {
    std::multimap<std::string, std::string> result;
    if(mod_editor->status)
      result.insert(std::pair<std::string,std::string>("status",mod_editor->status));

    if(mod_editor->visible)
      result.insert(std::pair<std::string,std::string>("visible",mod_editor->visible));

    if(mod_editor->maturity_option)
      result.insert(std::pair<std::string,std::string>("maturity_option",mod_editor->maturity_option));

    if(mod_editor->name)
      result.insert(std::pair<std::string,std::string>("name",mod_editor->name));

    if(mod_editor->name_id)
      result.insert(std::pair<std::string,std::string>("name_id",mod_editor->name_id));

    if(mod_editor->summary)
      result.insert(std::pair<std::string,std::string>("summary",mod_editor->summary));

    if(mod_editor->description)
      result.insert(std::pair<std::string,std::string>("description",mod_editor->description));

    if(mod_editor->homepage_url)
      result.insert(std::pair<std::string,std::string>("homepage_url",mod_editor->homepage_url));

    if(mod_editor->modfile)
      result.insert(std::pair<std::string,std::string>("modfile",mod_editor->modfile));

    if(mod_editor->metadata_blob)
      result.insert(std::pair<std::string,std::string>("metadata_blob",mod_editor->metadata_blob));

    return result;
  }
}
