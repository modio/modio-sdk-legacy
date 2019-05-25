#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>
#include <string.h>

void onSubmitReport(void *object, ModioResponse response)
{
  bool *wait = object;
  printf("On submit report response: %i\n", response.code);
  if (response.code == 201)
  {
    printf("Success\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Before requesting mods, let's define the query filters
  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter, 3);

  // Let's start by requesting a single mod
  char resource[50];
  printf("Enter the type of resource (games, mods or users): \n");
  fgets(resource, 50, stdin);
  resource[strcspn(resource, "\n")] = 0;

  char name[50];
  printf("Enter the name (informative title) of the report: \n");
  fgets(name, 50, stdin);
  name[strcspn(name, "\n")] = 0;

  char summary[50];
  printf("Enter summary of the report (detailed description): \n");
  fgets(summary, 50, stdin);
  summary[strcspn(summary, "\n")] = 0;

  printf("Please enter the of the resource id: \n");
  u32 id;
  scanf("%i", &id);

  printf("Please enter the type of report (0 - Generic report and 1 - DMCA report): \n");
  u32 type;
  scanf("%i", &type);

  printf("Submitting report...\n");

  // Now we finished setting up the filters we are ready to request the mods
  modioSubmitReport(&wait, resource, id, type, name, summary, &onSubmitReport);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
