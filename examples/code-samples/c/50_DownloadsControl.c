#include "modio_c.h"

bool finish = false;

void onModDownloaded(u32 response_code, u32 mod_id)
{
	printf("Downloaded Mod response: %i\n", response_code);
	if (response_code == 200)
	{
		printf("Mod %i downloaded successfully!\n", mod_id);
	}

	if (modioGetModDownloadQueueCount() == 0)
		finish = true;
}

int main(void)
{
	modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

	bool prompt_menu = true;

	// In this example we are going to queue two mods downloads.
	u32 mod_id;
	printf("Enter a mod id to download: \n");
	scanf("%i", &mod_id);
	modioDownloadMod(mod_id);

	printf("Enter another mod id to download: \n");
	scanf("%i", &mod_id);
	modioDownloadMod(mod_id);

	printf("Downloading mods...\n");

	modioSetDownloadListener(&onModDownloaded);

	while (!finish)
	{
		u32 queue_size = modioGetModDownloadQueueCount();
		if (queue_size != 0)
		{
			// The download queue contains all the information about the current downloads
			ModioQueuedModDownload *download_queue = malloc(queue_size * sizeof(*download_queue));
			modioGetModDownloadQueue(download_queue);

			printf("\n");
			printf("Download queue:\n");
			printf("===============\n");

			for (u32 i = 0; i < queue_size; i++)
			{
				ModioQueuedModDownload *queued_mod_download = &(download_queue[i]);
				printf("Name: %s\n", queued_mod_download->mod.name);
				printf("Id: %d\n", queued_mod_download->mod.id);
				double current_progress = queued_mod_download->current_progress;
				double total_size = queued_mod_download->total_size;
				printf("Download progress: %f%%\n", (current_progress / total_size) * 100.0);
				printf("\n");
			}

			if (prompt_menu && queue_size > 0)
			{
				u32 option;

				ModioQueuedModDownload *current_download = &(download_queue[0]);

				// Depending on the current download state, there are multiple options that can be given to the user to control their downloads
				switch (current_download->state)
				{
				case MODIO_MOD_STARTING_DOWNLOAD:
				{
					printf("Starting download. Please wait...\n");
					break;
				}
				case MODIO_MOD_DOWNLOADING:
				{
					if (current_download->current_progress == 0)
					{
						printf("Download started. Please wait...");
					}
					else
					{
						printf("Menu:\n");
						printf("=====\n");
						printf("1. Continue\n");
						printf("2. Pause\n");
						printf("3. Stop asking\n");
						printf("4. Prioritize download\n");
						printf("5. Exit\n");
						printf("Option: \n");
						scanf("%i", &option);

						if (option == 2)
							modioPauseDownloads();
						if (option == 3)
							prompt_menu = false;
						if (option == 4)
						{
							u32 mod_id;
							printf("Enter the mod id to prioritize: \n");
							scanf("%i", &mod_id);
							modioPrioritizeModDownload(mod_id);
						}
						if (option == 5)
							finish = true;
					}
					break;
				}
				case MODIO_MOD_PAUSING:
				{
					printf("Pausing. Please wait...\n");
					break;
				}
				case MODIO_MOD_PAUSED:
				{
					printf("Menu:\n");
					printf("=====\n");
					printf("1. Continue\n");
					printf("2. Resume\n");
					printf("3. Exit\n");
					printf("Option: \n");
					scanf("%i", &option);

					if (option == 2)
						modioResumeDownloads();
					if (option == 3)
						finish = true;
					break;
				}
				}
			}

			free(download_queue);
		}

		modioSleep(10);
		modioProcess();
		system("cls");
	}

	modioShutdown();

	printf("Process finished\n");

	return 0;
}
