#include "ModIOInstance.h"

namespace modio
{
  struct DownloadImageCall
  {
    void* object;
    const std::function<void(void* object, const ModioResponse&, const std::string& path)> callback;
  };

  struct EditModLogoCall
  {
    void* object;
    const std::function<void(void* object, const ModioResponse&, const int& mod_id)>& callback;
  };

  std::map<int, DownloadImageCall*> download_image_calls;
  std::map<int, EditModLogoCall*> edit_mod_logo_calls;

  void onDownloadImage(void* object, ModioResponse response, char* path)
  {
    int call_id = *((int*)object);

    download_image_calls[call_id]->callback(download_image_calls[call_id]->object, (const ModioResponse&)response, path);

    delete[] path;
    delete (int*)object;
    delete download_image_calls[call_id];
    download_image_calls.erase(call_id);
  }

  bool Instance::downloadImage(void* object, const std::string& image_url, const std::string& path, const std::function<void(void* object, const ModioResponse&, const std::string& path)>& callback)
  {
    const struct DownloadImageCall* download_image_call = new DownloadImageCall{object, callback};
    download_image_calls[this->current_call_id] = (DownloadImageCall*)download_image_call;

    modioDownloadImage((void*)new int(this->current_call_id), (char*)image_url.c_str(), (char*)path.c_str(), &onDownloadImage);

    this->current_call_id++;

    return true;
  }

  void onEditModLogo(void* object, ModioResponse response, int mod_id)
  {
    int call_id = *((int*)object);

    edit_mod_logo_calls[call_id]->callback(edit_mod_logo_calls[call_id]->object, (const ModioResponse&)response, mod_id);

    delete (int*)object;
    delete edit_mod_logo_calls[call_id];
    edit_mod_logo_calls.erase(call_id);
  }

  bool Instance::editModLogo(void* object, u32 mod_id, const std::string& path, const std::function<void(void* object, const ModioResponse&, const int& mod_id)>& callback)
  {
    const struct EditModLogoCall* edit_mod_logo_call = new EditModLogoCall{object, callback};
    edit_mod_logo_calls[this->current_call_id] = (EditModLogoCall*)edit_mod_logo_call;

    modioEditModLogo((void*)new int(this->current_call_id), mod_id, (char*)path.c_str(), &onEditModLogo);

    this->current_call_id++;

    return true;
  }
}
