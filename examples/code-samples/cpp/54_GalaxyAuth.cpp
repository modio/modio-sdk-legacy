#include "modio.h"
#include <iostream>

int main()
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

  // Auth works by providing the Appdata param given by the Galaxy SDK
  std::string appdata = "";
  modio_instance.galaxyAuth(appdata, [&](const modio::Response &response) {
    std::cout << "Response code: " << response.code << std::endl;

    if (response.code == 200)
      std::cout << "Successful Galaxy authentication";
    else
      std::cout << "Error while trying to authenticating to Galaxy" << std::endl;

    finish();
  });
  wait();

  std::cout << "Process finished" << std::endl;
  return 0;
}
