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

  // Auth works by providing the Appdata param given by the Oculus SDK
  std::string appdata = "";
  std::string nonce = "GALAXY NONCE PROOF HERE";
  std::string oculus_user_id = "123123";
  std::string access_token = "GALAXY AUTH TOKEN HERE";
  std::string email = ""; // Optional email param, "" will be ignored
  std::string device = "rift"; // rift and quest supported
  u32 date_expires = 0; // Optional expiration date param, 0 will be ignored
  modio_instance.oculusAuth(nonce, oculus_user_id, access_token, email, device, date_expires, [&](const modio::Response &response) {
    std::cout << "Response code: " << response.code << std::endl;

    if (response.code == 200)
      std::cout << "Successful Oculus authentication";
    else
      std::cout << "Error while authenticating to Oculus" << std::endl;

    finish();
  });
  wait();

  std::cout << "Process finished" << std::endl;
  return 0;
}
