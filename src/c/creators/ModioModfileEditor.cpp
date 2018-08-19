#include "c/creators/ModioModfileEditor.h"

extern "C"
{
  void modioInitModfileEditor(ModioModfileEditor* modfile_editor)
  {
    modfile_editor->version = NULL;
    modfile_editor->changelog = NULL;
    modfile_editor->metadata_blob = NULL;
    modfile_editor->active = NULL;
  }

  void modioSetModfileEditorVersion(ModioModfileEditor* modfile_editor, char* version)
  {
    if(modfile_editor->version)
      delete[] modfile_editor->version;

    modfile_editor->version = new char[strlen(version) + 1];
    strcpy(modfile_editor->version, version);
  }

  void modioSetModfileEditorChangelog(ModioModfileEditor* modfile_editor, char* changelog)
  {
    if(modfile_editor->changelog)
      delete[] modfile_editor->changelog;

    modfile_editor->changelog = new char[strlen(changelog) + 1];
    strcpy(modfile_editor->changelog, changelog);
  }

  void modioSetModfileEditorMetadataBlob(ModioModfileEditor* modfile_editor, char* metadata_blob)
  {
    if(modfile_editor->metadata_blob)
      delete[] modfile_editor->metadata_blob;

    modfile_editor->metadata_blob = new char[strlen(metadata_blob) + 1];
    strcpy(modfile_editor->metadata_blob, metadata_blob);
  }

  void modioSetModfileEditorActive(ModioModfileEditor* modfile_editor, bool active)
  {
    if(modfile_editor->active)
      delete[] modfile_editor->active;

    modfile_editor->active = new char[2];

    if(active)
      strcpy(modfile_editor->active, "1");
    else
      strcpy(modfile_editor->active, "0");
  }

  void modioFreeModfileEditor(ModioModfileEditor* modfile_editor)
  {
    if(modfile_editor->version)
      delete[] modfile_editor->version;

    if(modfile_editor->changelog)
      delete[] modfile_editor->changelog;

    if(modfile_editor->metadata_blob)
      delete[] modfile_editor->metadata_blob;

    if(modfile_editor->active)
      delete[] modfile_editor->active;
  }
}

namespace modio
{
  std::multimap<std::string, std::string> convertModfileEditorToMultimap(ModioModfileEditor* modfile_editor)
  {
    std::multimap<std::string, std::string> result;

    if(modfile_editor->version)
      result.insert(std::pair<std::string,std::string>("version",modfile_editor->version));

    if(modfile_editor->changelog)
      result.insert(std::pair<std::string,std::string>("changelog",modfile_editor->changelog));

    if(modfile_editor->metadata_blob)
      result.insert(std::pair<std::string,std::string>("metadata_blob",modfile_editor->metadata_blob));

    if(modfile_editor->active)
      result.insert(std::pair<std::string,std::string>("active",modfile_editor->active));

    return result;
  }
}
