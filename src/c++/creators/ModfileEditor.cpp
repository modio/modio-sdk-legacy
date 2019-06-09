#include "c++/creators/ModfileEditor.h"

namespace modio
{
  ModfileEditor::ModfileEditor()
  {
    modioInitModfileEditor(&modfile_editor);
  }

  void ModfileEditor::setVersion(const std::string& version)
  {
    modioSetModfileEditorVersion(&modfile_editor, version.c_str());
  }

  void ModfileEditor::setChangelog(const std::string& changelog)
  {
    modioSetModfileEditorChangelog(&modfile_editor, changelog.c_str());
  }

  void ModfileEditor::setMetadataBlob(const std::string& metadata_blob)
  {
    modioSetModfileEditorMetadataBlob(&modfile_editor, metadata_blob.c_str());
  }

  void ModfileEditor::setActive(bool active)
  {
    modioSetModfileEditorActive(&modfile_editor, active);
  }

  ModioModfileEditor* ModfileEditor::getModioModfileEditor()
  {
    return &modfile_editor;
  }

  ModfileEditor::~ModfileEditor()
  {
    modioFreeModfileEditor(&modfile_editor);
  }
}
