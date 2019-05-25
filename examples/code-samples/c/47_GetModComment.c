#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onGetModComment(void *object, ModioResponse response, ModioComment comment)
{
  bool *wait = object;
  printf("On mod get response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Id:\t\t%i\n", comment.id);
    printf("Mod id:\t\t%i\n", comment.mod_id);
    printf("Date added:\t%i\n", comment.date_added);
    printf("Reply id:\t%i\n", comment.reply_id);
    printf("Thread position:%s\n", comment.thread_position);
    printf("Karma:\t\t%i\n", comment.karma);
    printf("Karma guest:\t%i\n", comment.karma_guest);
    printf("Content:\t%s\n", comment.content);
    printf("User:\t\t%s\n", comment.user.username);
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // We request a single comment by providing it's id
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);
  printf("Please enter the comment id: \n");
  u32 comment_id;
  scanf("%i", &comment_id);

  printf("Getting mod comment...\n");
  modioGetModComment(&wait, mod_id, comment_id, &onGetModComment);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
