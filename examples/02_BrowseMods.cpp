#include "ModIOInstance.h"

int main(void)
{
  modio::Instance mod(7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]()
  {
    while (!finished)
    {
      modio::sleep(10);
      modioProcess();
    }
  };

  auto finish = [&]()
  {
    finished = true;
  };

  // Before requesting mods, let's define the query filters
  modio::Filter filter;
  filter.setFilterLimit(3);
  filter.addFilterLikeField("name", "Example Mod");
  filter.addFilterLikeField("description", "This mod description was added via the SDK examples. This mod description was added via the SDK examples.");

  std::cout <<"Getting mods..." << std::endl;

  // Now we finished setting up the filters we are ready to request the mods
  mod.getMods(filter, [&](const modio::Response& response, const std::vector<modio::Mod> & mods)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200)
    {
      std::cout << "Listing mods" << std::endl;
      std::cout << "============" << std::endl;
      for(int i=0; i < (int)mods.size(); i++)
      {
        std::cout << "Mod[" << i << "]" << std::endl;
        std::cout << "Id: \t" << mods[i].id << std::endl;
        std::cout << "Name:\t" << mods[i].name << std::endl;
        std::cout << "Name:\t" << mods[i].ratings.weighted_aggregate << std::endl;
      }

      // Additionally, we can access cursor data to ease future browsing queries
      std::cout << std::endl;
      std::cout << "Cursor data:" << std::endl;
      std::cout << "Cursor id: " << response.cursor_id << std::endl;
      std::cout << "Prev id: " << response.prev_id << std::endl;
      std::cout << "Next id: " << response.next_id << std::endl;
      std::cout << "Result count: " << response.result_count << std::endl;
    }
    finish();
  });

  wait();

  modioShutdown();

  std::cout << "Process finished" << std::endl;

  return 0;
}
