#include "modio.h"

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto finish = [&]() {
    finished = true;
  };

  auto wait = [&]() {
    while (!finished)
    {
      modio_instance.sleep(10);
      modio_instance.process();

      if (modio_instance.isLoggedIn())
      {
        std::cout << "You are subscribed to the following mods: " << std::endl;

        for (auto mod_id : modio_instance.getUserSubscriptionsIds())
        {
          std::cout << mod_id << std::endl;
        }

        std::cout << "Press ctrl-c to exit" << std::endl;
      }
      else
      {
        std::cout << "Please login before running this example" << std::endl;
        finish();
      }
    }
  };

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
