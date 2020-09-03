#include "modio.h"
#include <iostream>

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]() {
    while (!finished)
    {
      modio_instance.sleep(10);
      modio_instance.process();
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

  std::cout << "Getting events..." << std::endl;

  // Everything is setup up, let's retreive the events now
  modio_instance.getUserEvents(filter, [&](const modio::Response &response, const std::vector<modio::UserEvent> &events) {
    std::cout << "On user events response: " << response.code << std::endl;
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
        case MODIO_EVENT_USER_TEAM_JOIN:
          std::cout << "User has joined a team." << std::endl;
          break;
        case MODIO_EVENT_USER_TEAM_LEAVE:
          std::cout << "User has left a team." << std::endl;
          break;
        case MODIO_EVENT_USER_SUBSCRIBE:
          std::cout << "User has subscribed to a mod." << std::endl;
          break;
        case MODIO_EVENT_USER_UNSUBSCRIBE:
          std::cout << "User has un-subscribed from a mod." << std::endl;
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
