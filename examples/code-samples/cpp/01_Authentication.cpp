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

  // Check to see if we have a cookie and are already logged in
  if (!modio_instance.isLoggedIn())
  {
    std::string email;

    std::cout << "Enter your email: " << std::endl;
    std::cin >> email;

    // Auth works by sending an email with a code. Lets trigger that now
    modio_instance.emailRequest(email, [&](const modio::Response &response) {
      std::cout << "Response code: " << response.code << std::endl;

      if (response.code == 200)
      {
        std::string securityCode;
        std::cout << "Please enter the 5 digit security code: ";
        std::cin >> securityCode;

        // Finish the auth process by entering the security code
        modio_instance.emailExchange(securityCode, [&](const modio::Response &response) {
          std::cout << "Response code: " << response.code << std::endl;
          if (response.code == 200)
          {
            std::cout << "Code exchanged!" << std::endl;
          }
          else
          {
            std::cout << "Error exchanging code" << std::endl;
          }
          finish();
        });
      }
      else
      {
        std::cout << "Error sending code" << std::endl;
        finish();
      }
    });
    wait();
  }
  else
  {
    std::cout << "You are already logged in. Do you want to logout? (y/n)" << std::endl;
    std::string userOption;
    std::cin >> userOption;

    if (userOption == "y")
    {
      modio_instance.logout();
    }
  }

  std::cout << "Process finished" << std::endl;
  return 0;
}
