
namespace modio
{
  struct GetAllModEventsCall
  {
    const std::function<void(const modio::Response& response, std::vector<modio::ModEvent> mod_events)> callback;
  };

  struct ListendToModEventsCall
  {
    const std::function<void(const modio::Response& response, std::vector<modio::ModEvent> mod_events)> callback;
  };

  extern std::map<u32, GetAllModEventsCall*> get_all_mod_events_calls;
  extern ListendToModEventsCall* listend_to_mod_event_call;

  void onGetAllModEvents(void* object, ModioResponse modio_response, ModioModEvent* mod_events_array, u32 mod_events_array_size);
  void onListendToModEvents(ModioResponse modio_response, ModioModEvent* mod_events_array, u32 mod_events_array_size);
}
