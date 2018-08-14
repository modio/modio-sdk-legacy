#include "modio_c.h"

void onGetModStats(void *object, ModioResponse response, ModioModStats mod_stats)
{
  bool *wait = object;
  printf("On mod get response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Mod id: %i\n", mod_stats.mod_id);
    printf("Popularity rank position: %i\n", mod_stats.popularity_rank_position);
    printf("Popularity rank total mods: %i\n", mod_stats.popularity_rank_total_mods);
    printf("Downloads total: %i\n", mod_stats.downloads_total);
    printf("Subscribers total: %i\n", mod_stats.subscribers_total);
    printf("Ratings total: %i\n", mod_stats.ratings_total);
    printf("Ratings positive: %i\n", mod_stats.ratings_positive);
    printf("Ratings negative: %i\n", mod_stats.ratings_negative);
    printf("Ratings percentage positive: %i\n", mod_stats.ratings_percentage_positive);
    printf("Ratings weighted aggregate: %f\n", mod_stats.ratings_weighted_aggregate);
    printf("Ratings display text: %s\n", mod_stats.ratings_display_text);
    printf("Date expires: %i\n", mod_stats.date_expires);
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // We request a single mod stats by providing it's id
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Getting mod...\n");
  modioGetModStats(&wait, mod_id, &onGetModStats);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
