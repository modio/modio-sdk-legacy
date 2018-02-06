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

  time_t current_time;
  time (&current_time);

  modio::FilterCreator filter;
  filter.setLimit(7);
  filter.setCacheMaxAgeSeconds(100);
  // Let's filter from january first 2018 to the current date
  filter.addMinField("date_added", "1514780160");
  filter.addMaxField("date_added", modio::toString((u32)current_time));

  std::cout <<"Getting mods..." << std::endl;

  // Everything is setup up, let's retreive the events now
  modio_instance.getAllModEvents(filter, [&](const modio::Response& response, const std::vector<modio::ModEvent> & mod_events)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200)
    {
      // Just like the event listener, it returns an array of events
      for(auto& mod_event : mod_events)
      {
        std::cout << "Id: " <<  mod_event.id << std::endl;
        std::cout << "Mod id: " <<  mod_event.mod_id << std::endl;
        std::cout << "User id: " <<  mod_event.user_id << std::endl;
        std::cout << "Date added: " <<  (char*)ctime(&mod_event.date_added);
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
        std::cout << std::endl;
      }
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
