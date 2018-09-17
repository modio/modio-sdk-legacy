#include "modio_c.h"

void onEvent(ModioResponse response, ModioEvent *events_array, u32 events_array_size)
{
  // The mod event callback is triggered in a constant interval of time, 15 seconds by default
  printf("Event listener response: %i\n", response.code);
  if (response.code == 200)
  {
    // it returns an array of events so you can notify the user about it or do the correspoding changes
    for (u32 i = 0; i < events_array_size; i++)
    {
      printf("Event found!\n");
      printf("Id: %i\n", (int)events_array[i].id);
      printf("Mod id: %i\n", (int)events_array[i].mod_id);
      printf("User id: %i\n", (int)events_array[i].user_id);
      printf("Event type: ");
      switch (events_array[i].event_type)
      {
      case MODIO_EVENT_UNDEFINED:
        printf("Undefined\n");
        break;
      case MODIO_EVENT_MODFILE_CHANGED:
        printf("Modfile changed\n");
        break;
      case MODIO_EVENT_MOD_AVAILABLE:
        printf("Mod available\n");
        break;
      case MODIO_EVENT_MOD_UNAVAILABLE:
        printf("Mod unavailable\n");
        break;
      case MODIO_EVENT_MOD_EDITED:
        printf("Mod edited\n");
        break;
      }
      printf("\n");
    }
  }
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // You can register a function as callback for mod events
  modioSetEventListener(&onEvent);

  printf("Listening to mod events...\n");

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
