#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onGetAllDependencies(void *object, ModioResponse response, ModioDependency *dependencies_array, u32 dependencies_array_size)
{
	bool *wait = object;
	printf("Get all dependencies response: %i\n", response.code);
	if (response.code == 200)
	{
		printf("Listing dependencies:\n");
		for (u32 i = 0; i < dependencies_array_size; i++)
		{
			printf("%i\n", dependencies_array[i].mod_id);
		}
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

	// We request the list of dependencies by providing the Mod's id
	printf("Getting mod all dependencies...\n");
	modioGetAllModDependencies(&wait, mod_id, &onGetAllDependencies);

	while (wait)
	{
		modioProcess();
	}

	modioShutdown();

	printf("Process finished\n");

	return 0;
}
