
namespace modio
{
  struct InstallModCall
  {
    const std::function<void(const modio::Response& response)> callback;
  };

  extern std::map<u32, InstallModCall*> install_mod_calls;

  void onInstallModfile(void* object, ModioResponse modio_response);
}
