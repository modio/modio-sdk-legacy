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

  // Link mod.io accounts with service accounts such as Galaxy and Steam
  u32 service = MODIO_SERVICE_STEAM;
  std::string service_id = "";
  std::string email = "";
  modio_instance.linkExternalAccount(service, service_id, email, [&](const modio::Response &response) {
    std::cout << "Response code: " << response.code << std::endl;

    if (response.code == 200)
      std::cout << "Account linked successfully";
    else
      std::cout << "Could not link account" << std::endl;

    finish();
  });
  wait();

  std::cout << "Process finished" << std::endl;
  return 0;
}
