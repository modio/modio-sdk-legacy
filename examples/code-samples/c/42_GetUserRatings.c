#include "modio_c.h"
#include <time.h>

void onGetUserRatings(void *object, ModioResponse response, ModioRating *ratings_array, u32 ratings_array_size)
{
  bool *wait = object;
  printf("On get user ratings response: %i\n", response.code);

  for (u32 i = 0; i < ratings_array_size; i++)
  {
    printf("Game id: %i\n", (int)ratings_array[i].game_id);
    printf("Mod id: %i\n", (int)ratings_array[i].mod_id);
    printf("Rating: %i\n", (int)ratings_array[i].rating);
    printf("Date added: %i\n", (int)ratings_array[i].date_added);
    printf("\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  time_t current_time;
  time(&current_time);
  char current_time_str[12];
  sprintf(current_time_str, "%d", (int)current_time);

  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter, 10);
  // Let's filter from january first 2018 to the current date
  modioAddFilterMinField(&filter, "date_added", "1514780160");
  modioAddFilterMaxField(&filter, "date_added", current_time_str);

  printf("Getting users ratings...\n");

  // Everything is setup up, let's retreive the ratings now
  modioGetUserRatings(&wait, filter, &onGetUserRatings);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
