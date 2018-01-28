#include "modio_c.h"

void onEvent(ModioResponse response, ModioModEvent* mod_events_array, u32 mod_events_array_size)
{
  printf("Event listener response: %i\n", response.code);
  if(response.code == 200)
  {
    for(u32 i=0; i < mod_events_array_size; i++)
    {
      printf("Event found!\n");
      printf("Id: %i\n",(int)mod_events_array[i].id);
      printf("Mod id: %i\n",(int)mod_events_array[i].mod_id);
      printf("User id: %i\n",(int)mod_events_array[i].user_id);
      printf("Event type: ");
      switch( mod_events_array[i].event_type )
      {
        case EVENT_UNDEFINED:
        printf("Undefined\n");
        break;
        case EVENT_MODFILE_CHANGED:
        printf("Modfile changed\n");
        break;
        case EVENT_MOD_AVAILABLE:
        printf("Mod available\n");
        break;
        case EVENT_MOD_UNAVAILABLE:
        printf("Mod unavailable\n");
        break;
        case EVENT_MOD_EDITED:
        printf("Mod edited\n");
        break;
      }
      printf("\n");
    }
  }
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  modioListendToEvents(&onEvent);

  printf("Listening to mod events...\n");

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
