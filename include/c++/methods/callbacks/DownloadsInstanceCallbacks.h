namespace modio
{
  struct SetDownloadListenerCall
  {
    const std::function<void(u32 response_code, u32 mod_id)> callback;
  };

  extern SetDownloadListenerCall* set_download_listener_call;  

  void onDownloadListener(u32 response_code, u32 mod_id);  
}