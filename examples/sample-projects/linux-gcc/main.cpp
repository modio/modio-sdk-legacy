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

  // Before requesting mods, let's define the query filters
  modio::FilterCreator filter;
  filter.setLimit(7);
  filter.setCacheMaxAgeSeconds(100);

  std::cout <<"Getting mods..." << std::endl;

  // Now we finished setting up the filters we are ready to request the mods
  modio_instance.getAllMods(filter, [&](const modio::Response& response, const std::vector<modio::Mod> & mods)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200)
    {
      std::cout << "Listing mods" << std::endl;
      std::cout << "============" << std::endl;
      for(auto& mod : mods)
      {
        std::cout << "Id: \t" << mod.id << std::endl;
        std::cout << "Name:\t" << mod.name << std::endl;
      }

      // Additionally, we can access pagination data to ease future browsing queries
      std::cout << std::endl;
      std::cout << "Cursor data:" << std::endl;
      std::cout << "Result count: " << response.result_count << std::endl;
      std::cout << "Result limit: " << response.result_limit << std::endl;
      std::cout << "Result offset: " << response.result_offset << std::endl;
      std::cout << "Result total: " << response.result_total << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
