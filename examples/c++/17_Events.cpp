#include "modio.h"

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]()
  {
    while (!finished)
    {
      modio_instance.sleep(10);
      modioProcess();
    }
  };

  auto finish = [&]()
  {
    finished = true;
  };

  std::cout << "Listening to mod events..." << std::endl;

  // You can register a function as callback for mod events
  modio_instance.setModEventListener([&](const modio::Response& response, const std::vector<modio::ModEvent> & mod_events)
  {
    // The mod event callback is triggered in a constant interval of time, 15 seconds by default
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200)
    {
      // it returns a vector of events so you can notify the user about it or do the correspoding changes
      for(auto& mod_event : mod_events)
      {
        std::cout << "Event found!" << std::endl;
        std::cout << "Id: " <<  mod_event.id << std::endl;
        std::cout << "Mod id: " <<  mod_event.mod_id << std::endl;
        std::cout << "User id: " <<  mod_event.user_id << std::endl;
        std::cout << "Event Type: ";
        switch( mod_event.event_type )
        {
          case EVENT_UNDEFINED:
          std::cout<<"Undefined"<< std::endl;
          break;
          case EVENT_MODFILE_CHANGED:
          std::cout<<"Modfile changed"<< std::endl;
          break;
          case EVENT_MOD_AVAILABLE:
          std::cout<<"Mod available"<< std::endl;
          break;
          case EVENT_MOD_UNAVAILABLE:
          std::cout<<"Mod unavailable"<< std::endl;
          break;
          case EVENT_MOD_EDITED:
          std::cout<<"Mod edited"<< std::endl;
          break;
        }
        std::cout << "Date added: " <<  mod_event.date_added << std::endl;
        std::cout << std::endl;
      }
    }
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
