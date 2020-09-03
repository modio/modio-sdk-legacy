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

  std::string resource;
  std::cout << "Enter the resource: " << std::endl;
  std::cin >> resource;

  u32 id;
  std::cout << "Enter the id: " << std::endl;
  std::cin >> id;

  u32 type;
  std::cout << "Enter the type: " << std::endl;
  std::cin >> type;

  std::string name;
  std::cout << "Enter the name: " << std::endl;
  std::cin >> name;

  std::string summary;
  std::cout << "Enter the summary: " << std::endl;
  std::cin >> summary;

  std::cout << "Submitting report..." << std::endl;

  // Now we finished setting up the filters we are ready to request the mods
  modio_instance.submitReport(resource, id, type, name, summary, [&](const modio::Response &response) {
    std::cout << "Submit report response: " << response.code << std::endl;
    if (response.code == 201)
    {
      std::cout << "Success" << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
