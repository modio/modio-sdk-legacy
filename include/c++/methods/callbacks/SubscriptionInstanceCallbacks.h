namespace modio
{
  struct SubscribeModCall
  {
    const std::function<void(const modio::Response&, const modio::Mod& mod)> callback;
  };

  struct UnsubscribeModCall
  {
    const std::function<void(const modio::Response&)> callback;
  };

  extern std::map<u32, SubscribeModCall*> subscribe_mod_calls;
  extern std::map<u32, UnsubscribeModCall*> unsubscribe_mod_calls;

  void onSubscribeMod(void* object, ModioResponse modio_response, ModioMod mod);
  void onUnsubscribeMod(void* object, ModioResponse modio_response);
}
