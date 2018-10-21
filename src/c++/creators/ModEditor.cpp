#include "c++/creators/ModEditor.h"

namespace modio
{
ModEditor::ModEditor()
{
  modioInitModEditor(&mod_editor);
}

void ModEditor::setVisible(u32 visible)
{
  modioSetModEditorVisible(&mod_editor, visible);
}

void ModEditor::setStatus(u32 status)
{
  modioSetModEditorStatus(&mod_editor, status);
}

void ModEditor::setMaturityOption(u32 maturity_option)
{
  modioSetModEditorMaturityOption(&mod_editor, maturity_option);
}

void ModEditor::setName(const std::string &name)
{
  modioSetModEditorName(&mod_editor, (char *)name.c_str());
}

void ModEditor::setHomepageURL(const std::string &homepage_url)
{
  modioSetModEditorHomepageURL(&mod_editor, (char *)homepage_url.c_str());
}

void ModEditor::setSummary(const std::string &summary)
{
  modioSetModEditorSummary(&mod_editor, (char *)summary.c_str());
}

void ModEditor::setDescription(const std::string &description)
{
  modioSetModEditorDescription(&mod_editor, (char *)description.c_str());
}

void ModEditor::setMetadataBlob(const std::string &metadata_blob)
{
  modioSetModEditorMetadataBlob(&mod_editor, (char *)metadata_blob.c_str());
}

void ModEditor::setNameid(const std::string &name_id)
{
  modioSetModEditorNameid(&mod_editor, (char *)name_id.c_str());
}

void ModEditor::setModfile(u32 modfile)
{
  modioSetModEditorModfile(&mod_editor, modfile);
}

ModioModEditor *ModEditor::getModioModEditor()
{
  return &mod_editor;
}

ModEditor::~ModEditor()
{
  modioFreeModEditor(&mod_editor);
}
} // namespace modio
