#include "modio.h"

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

  // Before requesting mods, let's define the query filters
  modio::FilterCreator filter;
  filter.setLimit(3);
  filter.setCacheMaxAgeSeconds(100);

  std::cout << "Getting mods..." << std::endl;

  // Now we finished setting up the filters we are ready to request the mods
  modio_instance.getAllModStats(filter, [&](const modio::Response &response, const std::vector<modio::ModStats> &mods_stats) {
    std::cout << "On mod get response: " << response.code << std::endl;
    if (response.code == 200)
    {
      std::cout << "Listing mods stats" << std::endl;
      std::cout << "==================" << std::endl;
      for (auto &mod_stats : mods_stats)
      {
        std::cout << "Mod id: " << mod_stats.mod_id << std::endl;
        std::cout << "Popularity rank position: " << mod_stats.popularity_rank_position << std::endl;
        std::cout << "Popularity rank total mods: " << mod_stats.popularity_rank_total_mods << std::endl;
        std::cout << "Downloads total: " << mod_stats.downloads_total << std::endl;
        std::cout << "Subscribers total: " << mod_stats.subscribers_total << std::endl;
        std::cout << "Ratings total: " << mod_stats.ratings_total << std::endl;
        std::cout << "Ratings positive: " << mod_stats.ratings_positive << std::endl;
        std::cout << "Ratings negative: " << mod_stats.ratings_negative << std::endl;
        std::cout << "Ratings percentage positive: " << mod_stats.ratings_percentage_positive << std::endl;
        std::cout << "Ratings weighted aggregate: " << mod_stats.ratings_weighted_aggregate << std::endl;
        std::cout << "Ratings display text: " << mod_stats.ratings_display_text << std::endl;
        std::cout << "Date expires: " << mod_stats.date_expires << std::endl;
        std::cout << std::endl;
      }
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
