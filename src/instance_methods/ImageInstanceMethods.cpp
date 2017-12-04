#include "ModIOInstance.h"

namespace modio
{
  struct DownloadImageCall
  {
    const std::function<void(const modio::Response&, const std::string& path)> callback;
  };

  struct EditModLogoCall
  {
    const std::function<void(const modio::Response&, u32 mod_id)> callback;
  };

  std::map<int, DownloadImageCall*> download_image_calls;
  std::map<int, EditModLogoCall*> edit_mod_logo_calls;

  void onDownloadImage(void* object, ModioResponse modio_response, char* path)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);

    download_image_calls[call_id]->callback(response, path);

    delete[] path;
    delete (int*)object;
    delete download_image_calls[call_id];
    download_image_calls.erase(call_id);
  }

  void onEditModLogo(void* object, ModioResponse modio_response, int mod_id)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);

    edit_mod_logo_calls[call_id]->callback(response, mod_id);

    delete (int*)object;
    delete edit_mod_logo_calls[call_id];
    edit_mod_logo_calls.erase(call_id);
  }

  void Instance::downloadImage(const std::string& image_url, const std::string& path, const std::function<void(const modio::Response&, const std::string& path)>& callback)
  {
    const struct DownloadImageCall* download_image_call = new DownloadImageCall{callback};
    download_image_calls[this->current_call_id] = (DownloadImageCall*)download_image_call;

    modioDownloadImage((void*)new int(this->current_call_id), (char*)image_url.c_str(), (char*)path.c_str(), &onDownloadImage);

    this->current_call_id++;
  }

  void Instance::editModLogo(u32 mod_id, const std::string& path, const std::function<void(const modio::Response&, u32 mod_id)>& callback)
  {
    const struct EditModLogoCall* edit_mod_logo_call = new EditModLogoCall{callback};
    edit_mod_logo_calls[this->current_call_id] = (EditModLogoCall*)edit_mod_logo_call;

    modioEditModLogo((void*)new int(this->current_call_id), mod_id, (char*)path.c_str(), &onEditModLogo);

    this->current_call_id++;
  }
}
