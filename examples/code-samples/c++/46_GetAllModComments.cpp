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

  // Before requesting mods, let's define the query filters
  modio::FilterCreator filter;
  filter.setLimit(3);
  filter.setCacheMaxAgeSeconds(100);

  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;

  std::cout << "Getting mods..." << std::endl;

  // Now we finished setting up the filters we are ready to request the mods
  modio_instance.getAllModComments(mod_id, filter, [&](const modio::Response &response, const std::vector<modio::Comment> &comments) {
    std::cout << "On mod get response: " << response.code << std::endl;
    if (response.code == 200)
    {
      std::cout << "Listing comments" << std::endl;
      std::cout << "================" << std::endl;
      for (auto &comment : comments)
      {
        std::cout << "Id:\t\t" << comment.id << std::endl;
        std::cout << "Mod id:\t\t" << comment.mod_id << std::endl;
        std::cout << "Date added:\t" << comment.date_added << std::endl;
        std::cout << "Reply id:\t" << comment.reply_id << std::endl;
        std::cout << "Thread position:" << comment.thread_position << std::endl;
        std::cout << "Karma:\t\t" << comment.karma << std::endl;
        std::cout << "Karma guest:\t" << comment.karma_guest << std::endl;
        std::cout << "Content:\t" << comment.content << std::endl;
        std::cout << "User:\t\t" << comment.user.username << std::endl;
        std::cout << std::endl;
      }
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}