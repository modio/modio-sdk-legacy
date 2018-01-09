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

#define MODIO_NOT_ACCEPTED 0
#define MODIO_ACCEPTED     1
#define MODIO_ARCHIVED     2
#define MODIO_DELETED      3

#define MODIO_HIDDEN 0
#define MODIO_PUBLIC 1

typedef struct ModioListNode ModioListNode;
typedef struct ModioAvatar ModioAvatar;
typedef struct ModioError ModioError;
typedef struct ModioFilehash ModioFilehash;
typedef struct ModioHeader ModioHeader;
typedef struct ModioIcon ModioIcon;
typedef struct ModioImage ModioImage;
typedef struct ModioLogo ModioLogo;
typedef struct ModioMedia ModioMedia;
typedef struct ModioUser ModioUser;
typedef struct ModioModfile ModioModfile;
typedef struct ModioRatingSummary ModioRatingSummary;
typedef struct ModioTag ModioTag;
typedef struct ModioMod ModioMod;
typedef struct ModioResponse ModioResponse;
typedef struct ModioFilterCreator ModioFilterCreator;
typedef struct ModioModfileCreator ModioModfileCreator;
typedef struct ModioModfileEditor ModioModfileEditor;
typedef struct ModioModCreator ModioModCreator;
typedef struct ModioModEditor ModioModEditor;

struct ModioListNode
{
  char* value;
  ModioListNode* next;
};

struct ModioAvatar
{
  char* filename;
  char* original;
  char* thumb_50x50;
  char* thumb_100x100;
};

struct ModioError
{
  u32 code;
  char* message;
  char** errors_array;
  u32 errors_array_size;
};

struct ModioFilehash
{
  char* md5;
};

struct ModioHeader
{
  char* filename;
  char* original;
};

struct ModioIcon
{
  char* filename;
  char* original;
  char* thumb_64x64;
  char* thumb_128x128;
  char* thumb_256x256;
};

struct ModioImage
{
  char* filename;
  char* original;
  char* thumb_320x180;
};

struct ModioLogo
{
  char* filename;
  char* original;
  char* thumb_320x180;
  char* thumb_640x360;
  char* thumb_1280x720;
};

struct ModioMedia
{
  char** youtube_array;
  u32 youtube_size;
  char** sketchfab_array;
  u32 sketchfab_size;
  ModioImage* images_array;
  u32 images_size;
};

struct ModioUser
{
  u32 id;
  long date_online;
  char* username;
  char* name_id;
  char* timezone;
  char* language;
  char* profile_url;
  ModioAvatar avatar;
};

struct ModioModfile
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
};

struct ModioRatingSummary
{
  u32 total_ratings;
  u32 positive_ratings;
  u32 negative_ratings;
  u32 percentage_positive;
  double weighted_aggregate;
  char* display_text;
};

struct ModioTag
{
  u32 date_added;
  char* name;
};

struct ModioMod
{
  u32 id;
  u32 game_id;
  u32 status;
  u32 visible;
  long date_added;
  long date_updated;
  long date_live;
  char* homepage;
  char* name;
  char* name_id;
  char* summary;
  char* description;
  char* metadata_blob;
  char* profile_url;
  ModioLogo logo;
  ModioUser submitted_by;
  ModioModfile modfile;
  ModioMedia media;
  ModioRatingSummary rating_summary;
  ModioTag* tags_array;
  u32 tags_array_size;
};

struct ModioResponse
{
  u32 code;
  u32 result_count;
  u32 result_limit;
  i32 result_offset;
  ModioError error;
};

struct ModioFilterCreator
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
};

struct ModioModfileCreator
{
  char* path;
  char* version;
  char* changelog;
  char* active;
  char* filehash;
};

struct ModioModfileEditor
{
  char* version;
  char* changelog;
  char* active;
};

struct ModioModCreator
{
  char* visible;
  char* logo;
  char* name;
  char* name_id;
  char* summary;
  char* description;
  char* homepage;
  char* metadata_blob;
  ModioListNode* tags;
};

struct ModioModEditor
{
  char* visible;
  char* status;
  char* name;
  char* name_id;
  char* summary;
  char* description;
  char* homepage;
  char* modfile;
  char* metadata_blob;
  ModioListNode* tags;
};

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
void modioEditModfile(void* object, u32 mod_id, u32 modfile_id, ModioModfileEditor modfile_handler, void (*callback)(void* object, ModioResponse response, ModioModfile modfile));
void modioInstallModfile(void* object, u32 modfile_id, char* modfile_download, char* destination_path, void (*callback)(void* object, ModioResponse response));
u32 modioGetModfileState(u32 modfile_id);
double modioGetModfileDownloadPercentage(u32 modfile_id);
bool modioUninstallModfile(u32 modfile_id);
u32 modioGetInstalledModfilesCount();
u32 modioGetInstalledModfileId(u32 index);

//Mods Methods
void modioGetMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioMod mod));
void modioGetMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size));
void modioGetUserMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size));
void modioAddMod(void* object, ModioModCreator mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod mod));
void modioEditMod(void* object, u32 mod_id, ModioModEditor mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod mod));
void modioDeleteMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));
void modioSetUserModVote(void* object, u32 mod_id, bool vote_up, void (*callback)(void* object, ModioResponse response, u32 mod_id));
void modioSubscribeMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));
void modioUnsubscribeMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));

//Tags Methods
void modioGetTags(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id, ModioTag* tags_array, u32 tags_array_size));
void modioAddTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response, u32 mod_id));
void modioDeleteTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response, u32 mod_id));

//Filter Handler Methods
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

//Modfile Creator Handler Methods
void modioInitModfileCreator(ModioModfileCreator* modfile_creator);
void modioSetModfileCreatorPath(ModioModfileCreator* modfile_creator, char* path);
void modioSetModfileCreatorVersion(ModioModfileCreator* modfile_creator, char* version);
void modioSetModfileCreatorChangelog(ModioModfileCreator* modfile_creator, char* changelog);
void modioSetModfileCreatorActive(ModioModfileCreator* modfile_creator, bool active);
void modioSetModfileCreatorFilehash(ModioModfileCreator* modfile_creator, char* filehash);
void modioFreeModfileCreator(ModioModfileCreator* modfile_creator);

//Update Modfile Handler Methods
void modioInitModfileEditor(ModioModfileEditor* modfile_creator);
void modioSetModfileEditorVersion(ModioModfileEditor* modfile_creator, char* version);
void modioSetModfileEditorChangelog(ModioModfileEditor* modfile_creator, char* changelog);
void modioSetModfileEditorActive(ModioModfileEditor* modfile_creator, bool active);
void modioFreeModfileEditor(ModioModfileEditor* modfile_creator);

//Add Mod Handler Methods
void modioInitModCreator(ModioModCreator* mod_creator);
void modioSetModCreatorVisible(ModioModCreator* mod_creator, u32 visible);
void modioSetModCreatorLogoPath(ModioModCreator* mod_creator, char* logo_path);
void modioSetModCreatorName(ModioModCreator* mod_creator, char* name);
void modioSetModCreatorNameid(ModioModCreator* mod_creator, char* name_id);
void modioSetModCreatorSummary(ModioModCreator* mod_creator, char* summary);
void modioSetModCreatorDescription(ModioModCreator* mod_creator, char* description);
void modioSetModCreatorHomepage(ModioModCreator* mod_creator, char* homepage);
void modioSetModCreatorMetadataBlob(ModioModCreator* mod_creator, char* metadata_blob);
void modioAddModCreatorTag(ModioModCreator* mod_creator, char* tag);
void modioFreeModCreator(ModioModCreator* mod_creator);

//Update Mod Handler Methods
void modioInitModEditor(ModioModEditor* update_mod_handler);
void modioSetModEditorVisible(ModioModEditor* update_mod_handler, u32 visible);
void modioSetModEditorStatus(ModioModEditor* update_mod_handler, u32 status);
void modioSetModEditorName(ModioModEditor* update_mod_handler, char* name);
void modioSetModEditorNameid(ModioModEditor* update_mod_handler, char* name_id);
void modioSetModEditorSummary(ModioModEditor* update_mod_handler, char* summary);
void modioSetModEditorDescription(ModioModEditor* update_mod_handler, char* description);
void modioSetModEditorHomepage(ModioModEditor* update_mod_handler, char* homepage);
void modioSetModEditorModfile(ModioModEditor* update_mod_handler, u32 modfile);
void modioSetModEditorMetadataBlob(ModioModEditor* update_mod_handler, char* metadata_blob);
void modioFreeModEditor(ModioModEditor* update_mod_handler);
