#include "c++/creators/ModfileEditor.h"

namespace modio
{
  ModfileEditor::ModfileEditor()
  {
    this->modfile_editor = new ModioModfileEditor;
    modioInitModfileEditor(this->modfile_editor);
  }

  void ModfileEditor::setVersion(const std::string& version)
  {
    modioSetModfileEditorVersion(this->modfile_editor, (char*)version.c_str());
  }

  void ModfileEditor::setChangelog(const std::string& changelog)
  {
    modioSetModfileEditorChangelog(this->modfile_editor, (char*)changelog.c_str());
  }

  void ModfileEditor::setMetadataBlob(const std::string& metadata_blob)
  {
    modioSetModfileEditorMetadataBlob(this->modfile_editor, (char*)metadata_blob.c_str());
  }

  void ModfileEditor::setActive(bool active)
  {
    modioSetModfileEditorActive(this->modfile_editor, active);
  }

  ModioModfileEditor* ModfileEditor::getModioModfileEditor()
  {
    return this->modfile_editor;
  }

  ModfileEditor::~ModfileEditor()
  {
    modioFreeModfileEditor(this->modfile_editor);
  }
}
