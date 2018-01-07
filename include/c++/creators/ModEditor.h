#ifndef MODIO_MOD_EDITOR_H
#define MODIO_MOD_EDITOR_H

#include "c/creators/ModioModEditor.h"

namespace modio
{
  class MODIO_DLL ModEditor
  {
    ModioModEditor* mod_editor;
  public:
    ModEditor();
    void setName(const std::string& name);
    void setNameid(const std::string& name_id);
    void setSummary(const std::string& summary);
    void setDescription(const std::string& description);
    void setHomepage(const std::string& homepage);
    void setModfile(u32 modfile);
    void setMetadataBlob(const std::string& metadata_blob);
    void setStatus(u32 status);
    ModioModEditor* getModioModEditor();
    ~ModEditor();
  };
}

#endif
