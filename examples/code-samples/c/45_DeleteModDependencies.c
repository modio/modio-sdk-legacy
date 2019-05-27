#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onDeleteModDepencies(void *object, ModioResponse response)
{
	bool *wait = object;

	printf("Delete mod dependencies response: %i\n", response.code);
	if (response.code == 204)
	{
		printf("Dependencies deleted successfully\n");
	}

	*wait = false;
}

int main(void)
{
	modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

	bool wait = true;

	printf("Please enter the mod id: \n");
	u32 mod_id;
	scanf("%i", &mod_id);

	printf("Please enter the dependency id: \n");
	u32 dependency_id;
	scanf("%i", &dependency_id);

  int dependencies_array[1];
  dependencies_array[0] = dependency_id;

	// We delete dependencies from a mod by providing the mod and dependencies ids
	// Dependencies to be deleted are contained in an array
	printf("Deleting mod dependencies...\n");
	modioDeleteModDependencies(&wait, mod_id, dependencies_array, 1, &onDeleteModDepencies);

	while (wait)
	{
		modioProcess();
	}

	modioShutdown();

	printf("Process finished\n");

	return 0;
}
