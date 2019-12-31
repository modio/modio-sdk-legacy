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

  // We request the list of metadata key value pairs by providing the Mod's id
  modio_instance.getAuthenticatedUser([&](const modio::Response &response, const modio::User &user) {
    std::cout << "Get authenticated user response: " << response.code << std::endl;
    if (response.code == 200)
    {
      std::cout << "Id:\t" << user.id << std::endl;
      std::cout << "Username:\t" << user.username << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
