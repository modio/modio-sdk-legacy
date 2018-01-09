#include "c++/creators/ModEditor.h"

namespace modio
{
  ModEditor::ModEditor()
  {
    this->mod_editor = new ModioModEditor;
    modioInitModEditor(this->mod_editor);
  }

  void ModEditor::setVisible(u32 visible)
  {
    modioSetModEditorVisible(this->mod_editor, visible);
  }

  void ModEditor::setStatus(u32 status)
  {
    modioSetModEditorStatus(this->mod_editor, status);
  }

  void ModEditor::setName(const std::string& name)
  {
    modioSetModEditorName(this->mod_editor, (char*)name.c_str());
  }

  void ModEditor::setHomepage(const std::string& homepage)
  {
    modioSetModEditorHomepage(this->mod_editor, (char*)homepage.c_str());
  }

  void ModEditor::setSummary(const std::string& summary)
  {
    modioSetModEditorSummary(this->mod_editor, (char*)summary.c_str());
  }

  void ModEditor::setDescription(const std::string& description)
  {
    modioSetModEditorDescription(this->mod_editor, (char*)description.c_str());
  }

  void ModEditor::setMetadataBlob(const std::string& metadata_blob)
  {
    modioSetModEditorMetadataBlob(this->mod_editor, (char*)metadata_blob.c_str());
  }

  void ModEditor::setNameid(const std::string& name_id)
  {
    modioSetModEditorNameid(this->mod_editor, (char*)name_id.c_str());
  }

  void ModEditor::setModfile(u32 modfile)
  {
    modioSetModEditorModfile(this->mod_editor, modfile);
  }

  ModioModEditor* ModEditor::getModioModEditor()
  {
    return this->mod_editor;
  }

  ModEditor::~ModEditor()
  {
    modioFreeModEditor(this->mod_editor);
  }
}
