#include "ModIOInstance.h"

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds) // cross-platform sleep function
{
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(milliseconds * 1000);
#endif
}

int main()
{
  modio::Instance mod(7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]()
  {
    while (!finished)
    {
      //Sleep(10);
      sleep_ms(10);
      modioProcess();
    }
  };

  auto finish = [&]()
  {
    finished = true;
  };

  // Check to see if we have a cookie and are already logged in
  if (!mod.isLoggedIn())
  {
    std::string email;

    std::cout << "Enter your email: " << std::endl;
    std::cin >> email;

    // Auth works by sending an email with a code. Lets trigger that now
    mod.emailRequest(NULL, email, [&](void* object, const ModioResponse& response, const std::string& message)
    {
      std::cout << "Response code: " << response.code << std::endl;

      if (response.code == 200)
      {
        std::cout << "Message: " << message << std::endl;

        std::string securityCode;
        std::cout << "Please enter the 5 digit security code: ";
        std::cin >> securityCode;

        // Finish the auth process by entering the security code
        mod.emailExchange(NULL, securityCode, [&](void* object, const ModioResponse& response)
        {
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
        std::cout << "Error sending code" << endl;
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
      mod.logout();
    }
  }

  std::cout << "Process finished" << std::endl;
  return 0;
}
