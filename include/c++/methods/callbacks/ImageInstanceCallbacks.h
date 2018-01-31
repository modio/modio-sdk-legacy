
namespace modio
{
  struct DownloadImageCall
  {
    const std::function<void(const modio::Response&)> callback;
  };

  struct EditModLogoCall
  {
    const std::function<void(const modio::Response&, u32 mod_id)> callback;
  };

  extern std::map<u32, DownloadImageCall*> download_image_calls;
  extern std::map<u32, EditModLogoCall*> edit_mod_logo_calls;

  void onDownloadImage(void* object, ModioResponse modio_response);
  void onEditModLogo(void* object, ModioResponse modio_response, u32 mod_id);
}
