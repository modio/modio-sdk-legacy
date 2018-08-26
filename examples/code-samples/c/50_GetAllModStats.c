#include "modio_c.h"

void onGetAllModStats(void *object, ModioResponse response, ModioStats *mods_stats, u32 mods_stats_size)
{
  bool *wait = object;
  printf("Get mods response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Listing mods stats\n");
    printf("==================\n");
    for (u32 i = 0; i < mods_stats_size; i++)
    {
      printf("Mod[%i]\n", i);
      printf("Mod id: %i\n", mods_stats[i].mod_id);
      printf("Popularity rank position: %i\n", mods_stats[i].popularity_rank_position);
      printf("Popularity rank total mods: %i\n", mods_stats[i].popularity_rank_total_mods);
      printf("Downloads total: %i\n", mods_stats[i].downloads_total);
      printf("Subscribers total: %i\n", mods_stats[i].subscribers_total);
      printf("Ratings total: %i\n", mods_stats[i].ratings_total);
      printf("Ratings positive: %i\n", mods_stats[i].ratings_positive);
      printf("Ratings negative: %i\n", mods_stats[i].ratings_negative);
      printf("Ratings percentage positive: %i\n", mods_stats[i].ratings_percentage_positive);
      printf("Ratings weighted aggregate: %f\n", mods_stats[i].ratings_weighted_aggregate);
      printf("Ratings display text: %s\n", mods_stats[i].ratings_display_text);
      printf("Date expires: %i\n", mods_stats[i].date_expires);
    }
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Before requesting mods, let's define the query filters
  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter, 3);

  printf("Getting mods stats...\n");

  // Now we finished setting up the filters we are ready to request the mods
  modioGetAllModStats(&wait, filter, &onGetAllModStats);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
