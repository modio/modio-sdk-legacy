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

  // Before requesting mod stats, let's define the query filters
  modio::FilterCreator filter;
  filter.setLimit(3);
  filter.setCacheMaxAgeSeconds(100);

  std::cout << "Getting mods..." << std::endl;

  // Now we finished setting up the filters we are ready to request the stats
  modio_instance.getAllModStats(filter, [&](const modio::Response &response, const std::vector<modio::Stats> &mods_stats) {
    std::cout << "On mod get response: " << response.code << std::endl;
    if (response.code == 200)
    {
      std::cout << "Listing mods stats" << std::endl;
      std::cout << "==================" << std::endl;
      for (auto &stats : mods_stats)
      {
        std::cout << "Mod id: " << stats.mod_id << std::endl;
        std::cout << "Popularity rank position: " << stats.popularity_rank_position << std::endl;
        std::cout << "Popularity rank total mods: " << stats.popularity_rank_total_mods << std::endl;
        std::cout << "Downloads total: " << stats.downloads_total << std::endl;
        std::cout << "Subscribers total: " << stats.subscribers_total << std::endl;
        std::cout << "Ratings total: " << stats.ratings_total << std::endl;
        std::cout << "Ratings positive: " << stats.ratings_positive << std::endl;
        std::cout << "Ratings negative: " << stats.ratings_negative << std::endl;
        std::cout << "Ratings percentage positive: " << stats.ratings_percentage_positive << std::endl;
        std::cout << "Ratings weighted aggregate: " << stats.ratings_weighted_aggregate << std::endl;
        std::cout << "Ratings display text: " << stats.ratings_display_text << std::endl;
        std::cout << "Date expires: " << stats.date_expires << std::endl;
        std::cout << std::endl;
      }
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
