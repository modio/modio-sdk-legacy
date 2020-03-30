#ifndef MODIO_DOWNLOADS_CALLBACKS_H
#define MODIO_DOWNLOADS_CALLBACKS_H

#include "../../../Globals.h"
#include "../../../ModioUtility.h"

struct CheckIfModsAreUpdatedParams
{
	void* object;
	u32 call_count;
	bool mods_are_updated;
	void(*callback)(void* object, ModioResponse response, bool mods_are_updated);
};

struct UpdateModsParams
{
	void* object;
	void(*callback)(void* object, ModioResponse response, bool mods_are_updated);
};

extern std::map< u32, CheckIfModsAreUpdatedParams* > check_if_mods_are_updated_callbacks;
extern std::map< u32, UpdateModsParams* > update_mods_callbacks;

void onModioCheckIfModsAreUpdated(void *object, ModioResponse response, ModioMod *mods, u32 mods_size);
void onModioUpdateMods(void *object, ModioResponse response, bool mods_are_updated);
void clearDownloadsCallbackParams();

#endif
