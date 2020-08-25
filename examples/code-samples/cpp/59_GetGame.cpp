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

  // To retreive a single game we just need the game id
  u32 game_id;
  std::cout << "Enter the game id: " << std::endl;
  std::cin >> game_id;

  std::cout << "Getting game..." << std::endl;

  modio_instance.getGame(game_id, [&](const modio::Response& response, const modio::Game& game) {
    std::cout << "On get game response: " << response.code << std::endl;
    if (response.code == 200)
    {
      std::cout << "Id: \t" << game.id << std::endl;
      std::cout << "Version:\t" << game.name << std::endl;
      std::cout << "Summary:\t" << game.summary << std::endl;
    }
    finish();
    });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
