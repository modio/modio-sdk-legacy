#include "modio_c.h"

void onGetModStats(void *object, ModioResponse response, ModioStats stats)
{
  bool *wait = object;
  printf("On mod get response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Mod id: %i\n", stats.mod_id);
    printf("Popularity rank position: %i\n", stats.popularity_rank_position);
    printf("Popularity rank total mods: %i\n", stats.popularity_rank_total_mods);
    printf("Downloads total: %i\n", stats.downloads_total);
    printf("Subscribers total: %i\n", stats.subscribers_total);
    printf("Ratings total: %i\n", stats.ratings_total);
    printf("Ratings positive: %i\n", stats.ratings_positive);
    printf("Ratings negative: %i\n", stats.ratings_negative);
    printf("Ratings percentage positive: %i\n", stats.ratings_percentage_positive);
    printf("Ratings weighted aggregate: %f\n", stats.ratings_weighted_aggregate);
    printf("Ratings display text: %s\n", stats.ratings_display_text);
    printf("Date expires: %i\n", stats.date_expires);
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // We request a single mod stats by providing the mod id
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
