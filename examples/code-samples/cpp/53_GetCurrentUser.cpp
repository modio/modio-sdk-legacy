#include "modio.h"
#include <iostream>

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto finish = [&]() {
    finished = true;
  };

  // Use getCurrentUser in conjuction with the isLoggedIn to check the current user cache
  if(modio_instance.isLoggedIn())
  {
    std::cout << "Logged in as " << modio_instance.getCurrentUser().username << std::endl;
  }else
  {
    std::cout << "You are not logged in." << std::endl;    
  }
  

  std::cout << "Process finished" << std::endl;

  return 0;
}
