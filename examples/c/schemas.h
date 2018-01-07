#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int u32;
typedef int i32;

#define MODIO_DEBUGLEVEL_LOG      2
#define MODIO_DEBUGLEVEL_WARNING  1
#define MODIO_DEBUGLEVEL_ERROR    0

#define MODIO_MODFILE_NOT_INSTALLED 0
#define MODIO_MODFILE_INSTALLED     1
#define MODIO_MODFILE_INSTALLING    2

struct ModioListNode
{
  char* value;
  struct ModioListNode* next;
};

typedef struct ModioListNode ModioListNode;

typedef struct
{
  char* filename;
  char* original;
  char* thumb_50x50;
  char* thumb_100x100;
}ModioAvatar;

typedef struct
{
  u32 code;
  char* message;
  char** errors_array;
  u32 errors_array_size;
}ModioError;

typedef struct
{
  char* md5;
}ModioFilehash;

typedef struct
{
  char* filename;
  char* original;
}ModioHeader;

typedef struct
{
  char* filename;
  char* original;
  char* thumb_64x64;
  char* thumb_128x128;
  char* thumb_256x256;
}ModioIcon;

typedef struct
{
  char* filename;
  char* original;
  char* thumb_320x180;
}ModioImage;

typedef struct
{
  char* filename;
  char* original;
  char* thumb_320x180;
  char* thumb_640x360;
  char* thumb_1280x720;
}ModioLogo;

typedef struct
{
  char** youtube_array;
  u32 youtube_size;
  char** sketchfab_array;
  u32 sketchfab_size;
  ModioImage* images_array;
  u32 images_size;
}ModioMedia;

typedef struct
{
  u32 id;
  long date_online;
  char* username;
  char* name_id;
  char* timezone;
  char* language;
  char* profile_url;
  ModioAvatar avatar;
}ModioUser;

typedef struct
{
  u32 id;
  u32 mod_id;
  u32 virus_status;
  u32 virus_positive;
  long date_added;
  long date_scanned;
  long filesize;
  char* filename;
  char* version;
  char* virustotal_hash;
  char* changelog;
  char* download_url;
  ModioFilehash filehash;
}ModioModfile;

typedef struct
{
  u32 total_ratings;
  u32 positive_ratings;
  u32 negative_ratings;
  u32 percentage_positive;
  double weighted_aggregate;
  char* display_text;
}ModioRatingSummary;

typedef struct
{
  u32 date_added;
  char* name;
}ModioTag;

typedef struct
{
  u32 id;
  u32 game_id;
  long date_added;
  long date_live;
  long date_updated;
  char* homepage;
  char* name;
  char* name_id;
  char* summary;
  char* description;
  char* metadata_blob;
  char* profile_url;
  ModioLogo logo;
  ModioUser submitted_by;
  ModioMedia media;
  ModioModfile modfile;
  ModioRatingSummary rating_summary;
  ModioTag* tags_array;
  u32 tags_array_size;
}ModioMod;

typedef struct
{
  u32 code;
  u32 result_count;
  u32 result_limit;
  i32 result_offset;
  ModioError error;
}ModioResponse;

typedef struct
{
  char* sort;
  char* limit;
  char* offset;
  char* full_text_search;
  ModioListNode* field_value_list;
  ModioListNode* like_list;
  ModioListNode* not_like_list;
  ModioListNode* in_list;
  ModioListNode* not_in_list;
  ModioListNode* min_list;
  ModioListNode* max_list;
  ModioListNode* smaller_than_list;
  ModioListNode* greater_than_list;
  ModioListNode* not_equal_list;
}ModioFilterCreator;

typedef struct
{
  char* path;
  char* version;
  char* changelog;
  char* active;
  char* filehash;
}ModioModfileCreator;

typedef struct
{
  char* version;
  char* changelog;
  char* active;
}ModioModfileEditor;

typedef struct
{
  char* logo;
  char* name;
  char* name_id;
  char* summary;
  char* description;
  char* homepage;
  char* metadata_blob;
  ModioListNode* tags;
}ModioModCreator;

typedef struct
{
  char* name;
  char* name_id;
  char* summary;
  char* description;
  char* homepage;
  char* modfile;
  char* metadata_blob;
  char* status;
  ModioListNode* tags;
}ModioModEditor;

//General Methods
void modioInit(u32 game_id, char* api_key);
//void init(int game_id, char* api_key, char* root_path);
void modioShutdown();
//CurrentDownloadInfo modioGetCurrentDownloadInfo();
void modioPauseCurrentDownload();
void modioSetDebugLevel(u32 debug_level);
void modioProcess();
void modioSleep(u32 milliseconds);

//Authentication methods
void modioEmailRequest(void* object, char* email, void (*callback)(void* object, ModioResponse response));
void modioEmailExchange(void* object, char* security_code, void (*callback)(void* object, ModioResponse response));
bool modioIsLoggedIn();
void modioLogout();

//Image Methods
void modioDownloadImage(void* object, char* image_url, char* path, void (*callback)(void* object, ModioResponse response));
void modioEditModLogo(void* object, u32 mod_id, char* path, void (*callback)(void* object, ModioResponse response, u32 mod_id));

//Modfile Methods
void modioAddModfile(void* object, u32 mod_id, ModioModfileCreator modfile_creator, void (*callback)(void* object, ModioResponse response, ModioModfile modfile));
void modioEditModfile(void* object, u32 mod_id, u32 modfile_id, ModioModfileEditor modfile_editor, void (*callback)(void* object, ModioResponse response, ModioModfile modfile));
void modioInstallModfile(void* object, u32 modfile_id, char* modfile_download, char* destination_path, void (*callback)(void* object, ModioResponse response));
u32 modioGetModfileState(u32 modfile_id);
double modioGetModfileDownloadPercentage(u32 modfile_id);
bool modioUninstallModfile(u32 modfile_id);
u32 modioGetInstalledModfilesCount();
u32 modioGetInstalledModfileId(u32 index);

//Mods Methods
void modioGetMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size));
void modioAddMod(void* object, ModioModCreator mod_creator, void (*callback)(void* object, ModioResponse response, ModioMod mod));
void modioEditMod(void* object, u32 mod_id, ModioModEditor mod_editor, void (*callback)(void* object, ModioResponse response, ModioMod mod));
void modioDeleteMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));
void modioSetUserModVote(void* object, u32 mod_id, bool vote_up, void (*callback)(void* object, ModioResponse response, u32 mod_id));
void modioSubscribeMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));
void modioUnsubscribeMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));

//Tags Methods
void modioGetTags(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id, ModioTag* tags_array, u32 tags_array_size));
void modioAddTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response, u32 mod_id));
void modioDeleteTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response, u32 mod_id));

//Filter Creator Methods
void modioInitFilter(ModioFilterCreator* filter);
void modioSetFilterSort(ModioFilterCreator* filter, char* field, bool ascending);
void modioSetFilterLimit(ModioFilterCreator* filter, u32 limit);
void modioSetFilterOffset(ModioFilterCreator* filter, u32 offset);
void modioSetFilterFullTextSearch(ModioFilterCreator* filter, char* text);
void modioAddFilterFieldValue(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterLikeField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterNotLikeField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterInField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterNotInField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterMinField(ModioFilterCreator* filter, char* field, double value);
void modioAddFilterMaxField(ModioFilterCreator* filter, char* field, double value);
void modioAddFilterSmallerThanField(ModioFilterCreator* filter, char* field, double value);
void modioAddFilterGreaterThanField(ModioFilterCreator* filter, char* field, double value);
void modioAddFilterNotEqualField(ModioFilterCreator* filter, char* field, char* value);
void modioFreeFilter(ModioFilterCreator* filter);

//Modfile Creator Methods
void modioInitModfileCreator(ModioModfileCreator* modfile_creator);
void modioSetModfileCreatorPath(ModioModfileCreator* modfile_creator, char* path);
void modioSetModfileCreatorVersion(ModioModfileCreator* modfile_creator, char* version);
void modioSetModfileCreatorChangelog(ModioModfileCreator* modfile_creator, char* changelog);
void modioSetModfileCreatorActive(ModioModfileCreator* modfile_creator, bool active);
void modioSetModfileCreatorFilehash(ModioModfileCreator* modfile_creator, char* filehash);
void modioFreeModfileCreator(ModioModfileCreator* modfile_creator);

//Modfile Editor Methods
void modioInitModfileEditor(ModioModfileEditor* modfile_creator);
void modioSetModfileEditorVersion(ModioModfileEditor* modfile_creator, char* version);
void modioSetModfileEditorChangelog(ModioModfileEditor* modfile_creator, char* changelog);
void modioSetModfileEditorActive(ModioModfileEditor* modfile_creator, bool active);
void modioFreeModfileEditor(ModioModfileEditor* modfile_creator);

//Mod Creator Methods
void modioInitModCreator(ModioModCreator* mod_creator);
void modioSetModCreatorLogoPath(ModioModCreator* mod_creator, char* logo_path);
void modioSetModCreatorName(ModioModCreator* mod_creator, char* name);
void modioSetModCreatorNameid(ModioModCreator* mod_creator, char* name_id);
void modioSetModCreatorSummary(ModioModCreator* mod_creator, char* summary);
void modioSetModCreatorDescription(ModioModCreator* mod_creator, char* description);
void modioSetModCreatorHomepage(ModioModCreator* mod_creator, char* homepage);
void modioSetModCreatorMetadataBlob(ModioModCreator* mod_creator, char* metadata_blob);
void modioAddModCreatorTag(ModioModCreator* mod_creator, char* tag);
void modioFreeModCreator(ModioModCreator* mod_creator);

//Mod Editor Methods
void modioInitModEditor(ModioModEditor* mod_editor);
void modioSetModEditorName(ModioModEditor* mod_editor, char* name);
void modioSetModEditorNameid(ModioModEditor* mod_editor, char* name_id);
void modioSetModEditorSummary(ModioModEditor* mod_editor, char* summary);
void modioSetModEditorDescription(ModioModEditor* mod_editor, char* description);
void modioSetModEditorHomepage(ModioModEditor* mod_editor, char* homepage);
void modioSetModEditorModfile(ModioModEditor* mod_editor, u32 modfile);
void modioSetModEditorMetadataBlob(ModioModEditor* mod_editor, char* metadata_blob);
void modioSetModEditorStatus(ModioModEditor* mod_editor, char* status);
void modioFreeModEditor(ModioModEditor* mod_editor);
