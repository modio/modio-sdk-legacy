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

  u32 mod_id, comment_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;
  std::cout << "Enter the comment id: " << std::endl;
  std::cin >> comment_id;

  std::cout << "Getting comment..." << std::endl;

  modio_instance.getModComment(mod_id, comment_id, [&](const modio::Response &response, const modio::Comment &comment) {
    std::cout << "On get comment response: " << response.code << std::endl;
    if (response.code == 200)
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
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
