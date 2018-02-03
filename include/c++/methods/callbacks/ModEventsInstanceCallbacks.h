
namespace modio
{
  struct GetModEventsCall
  {
    const std::function<void(const modio::Response& response, std::vector<modio::ModEvent> mod_events)> callback;
  };

  struct GetAllModEventsCall
  {
    const std::function<void(const modio::Response& response, std::vector<modio::ModEvent> mod_events)> callback;
  };

  struct SetModEventListenerCall
  {
    const std::function<void(const modio::Response& response, std::vector<modio::ModEvent> mod_events)> callback;
  };

  extern std::map<u32, GetModEventsCall*> get_mod_events_calls;
  extern std::map<u32, GetAllModEventsCall*> get_all_mod_events_calls;
  extern SetModEventListenerCall* set_mod_event_listener_call;

  void onGetModEvents(void* object, ModioResponse modio_response, ModioModEvent* mod_events_array, u32 mod_events_array_size);
  void onGetAllModEvents(void* object, ModioResponse modio_response, ModioModEvent* mod_events_array, u32 mod_events_array_size);
  void onSetModEventListener(ModioResponse modio_response, ModioModEvent* mod_events_array, u32 mod_events_array_size);
}
