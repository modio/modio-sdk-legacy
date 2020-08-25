#include "modio.h"
#include <iostream>
#include <time.h>

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]() {
    while (!finished)
    {
      modio_instance.sleep(10);
      modioProcess();
    }
  };

  auto finish = [&]() {
    finished = true;
  };

  time_t current_time;
  time(&current_time);

  modio::FilterCreator filter;
  filter.setLimit(7);
  filter.setCacheMaxAgeSeconds(100);
  // Let's filter from january first 2018 to the current date
  filter.addMinField("date_added", "1514780160");
  filter.addMaxField("date_added", modio::toString((u32)current_time));

  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;

  std::cout << "Getting events..." << std::endl;

  // Everything is setup up, let's retreive the events now
  modio_instance.getEvents(mod_id, filter, [&](const modio::Response &response, const std::vector<modio::ModEvent> &events) {
    std::cout << "On get events response: " << response.code << std::endl;
    if (response.code == 200)
    {
      // Just like the event listener, it returns an array of events
      for (auto &event : events)
      {
        std::cout << "Id: " << event.id << std::endl;
        std::cout << "Mod id: " << event.mod_id << std::endl;
        std::cout << "User id: " << event.user_id << std::endl;
        const time_t date_added = (time_t)event.date_added;
        std::cout << "Date added: " << ctime(&date_added);
        std::cout << "Event Type: ";
        switch (event.event_type)
        {
        case MODIO_EVENT_UNDEFINED:
          std::cout << "Undefined" << std::endl;
          break;
        case MODIO_EVENT_MODFILE_CHANGED:
          std::cout << "Modfile changed" << std::endl;
          break;
        case MODIO_EVENT_MOD_AVAILABLE:
          std::cout << "Mod available" << std::endl;
          break;
        case MODIO_EVENT_MOD_UNAVAILABLE:
          std::cout << "Mod unavailable" << std::endl;
          break;
        case MODIO_EVENT_MOD_EDITED:
          std::cout << "Mod edited" << std::endl;
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
