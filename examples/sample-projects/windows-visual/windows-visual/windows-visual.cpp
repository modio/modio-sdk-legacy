#include "stdafx.h"
#include <iostream>
#include "modio.h"

int main(void)
{
  // Retreive your game id and api key from the mod.io web to initialize mod.io
  // First, experiment with the test environment under test.mod.io and once you're ready to launch, switch to the live environment by passing the MODIO_ENVIRONMENT_LIVE flag
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, YOUR_GAME_ID, "YOUR_API_KEY");

  volatile static bool finished = false;

  auto wait = [&]()
  {
    while (!finished)
    {
      modio_instance.sleep(10);
      // Add the process funcion to your game loop to process mod.io funcionality asynchronously
      modioProcess();
    }
  };

  auto finish = [&]()
  {
    finished = true;
  };

  // Before requesting mods, let's define the query filters
  modio::FilterCreator filter;
  filter.setLimit(5);

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
