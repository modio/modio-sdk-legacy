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

  std::cout << "Getting ratings..." << std::endl;

  // Everything is setup up, let's retreive the ratings now
  modio_instance.getUserRatings(filter, [&](const modio::Response &response, const std::vector<modio::Rating> &ratings) {
    std::cout << "On user ratings response: " << response.code << std::endl;
    if (response.code == 200)
    {
      for (auto &rating : ratings)
      {
        std::cout << "Game id: " << rating.game_id << std::endl;
        std::cout << "Mod id: " << rating.mod_id << std::endl;
        std::cout << "Rating: " << rating.rating << std::endl;
        std::cout << "Date added: " << rating.date_added << std::endl;
        std::cout << std::endl;
      }
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
