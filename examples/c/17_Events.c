#include "modio_c.h"

void onEvent(ModioResponse response, ModioModEvent* mod_events_array, u32 mod_events_array_size)
{
  if(response.code == 200)
  {
    printf("Listing events:\n");

    for(u32 i=0; i < mod_events_array_size; i++)
    {
      printf("Id: %i\n",(int)mod_events_array[i].id);
      printf("Date added: %i\n",(int)mod_events_array[i].date_added);
      printf("Event type: %i\n",(int)mod_events_array[i].event_type);
      printf("Mod id: %i\n",(int)mod_events_array[i].mod_id);
    }
  }
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  modioListendToEvents(&onEvent);

  printf("Getting mods...\n");

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
