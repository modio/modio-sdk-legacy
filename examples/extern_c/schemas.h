#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int u32;
typedef int i32;

typedef struct
{
  char* value;
  struct ModioListNode* next;
}ModioListNode;

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
}ModioFilterHandler;

typedef struct
{
  char* path;
  char* version;
  char* changelog;
  char* active;
}ModioModfileHandler;

typedef struct
{
  char* logo;
  char* name;
  char* homepage;
  char* summary;
  char* price;
  char* stock;
  char* description;
  char* metadata;
  char* nameid;
  char* modfile;
  ModioListNode* tags;
}ModioModHandler;

//General Methods
void modioInit(int game_id, char* api_key);
//void init(int game_id, char* api_key, char* root_path);
void modioShutdown();
//CurrentDownloadInfo modioGetCurrentDownloadInfo();
void modioPauseCurrentDownload();
void modioSetDebugLevel(unsigned int debug_level);
void modioProcess();

//Authentication methods
void modioEmailRequest(void* object, char* email, void (*callback)(void* object, ModioResponse response));
void modioEmailExchange(void* object, char* security_code, void (*callback)(void* object, ModioResponse response));
bool modioIsLoggedIn();
void modioLogout();

//Image Methods
void modioDownloadImage(void* object, char* image_url, char* path, void (*callback)(void* object, ModioResponse response));
void modioEditModLogo(void* object, int mod_id, char* path, void (*callback)(void* object, ModioResponse response, int mod_id));

//Modfile Methods
void modioAddModfile(void* object, int mod_id, ModioModfileHandler modfile_handler, void (*callback)(void* object, ModioResponse response, ModioModfile modfile));
void modioEditModfile(void* object, int mod_id, int modfile_id, ModioModfileHandler modfile_handler, void (*callback)(void* object, ModioResponse response, ModioModfile modfile));
void modioInstallModfile(void* object, u32 modfile_id, char* modfile_download, char* destination_path, void (*callback)(void* object, ModioResponse response));
int modioGetModfileState(int modfile_id);
double modioGetModfileDownloadPercentage(int modfile_id);

//Mods Methods
void modioGetMods(void* object, ModioFilterHandler filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], int mods_size));
void modioAddMod(void* object, ModioModHandler mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod mod));
void modioEditMod(void* object, int mod_id, ModioModHandler mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod mod));
void modioDeleteMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id));
void modioSetUserModVote(void* object, int mod_id, bool vote_up, void (*callback)(void* object, ModioResponse response, int mod_id));
void modioSubscribeMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id));
void modioUnsubscribeMod(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id));

//Tags Methods
void modioGetTags(void* object, int mod_id, void (*callback)(void* object, ModioResponse response, int mod_id, ModioTag* tags_array, int tags_array_size));
void modioAddTags(void* object, int mod_id, char** tags_array, int tags_array_size, void (*callback)(void* object, ModioResponse response, int mod_id));
void modioDeleteTags(void* object, int mod_id, char** tags_array, int tags_array_size, void (*callback)(void* object, ModioResponse response, int mod_id));

//Filter Handler Methods
void modioInitFilter(ModioFilterHandler* filter);
void modioSetFilterSort(ModioFilterHandler* filter, char* field, bool ascending);
void modioSetFilterLimit(ModioFilterHandler* filter, int limit);
void modioSetFilterOffset(ModioFilterHandler* filter, int offset);
void modioSetFilterFullTextSearch(ModioFilterHandler* filter, char* text);
void modioAddFilterFieldValue(ModioFilterHandler* filter, char* field, char* value);
void modioAddFilterLikeField(ModioFilterHandler* filter, char* field, char* value);
void modioAddFilterNotLikeField(ModioFilterHandler* filter, char* field, char* value);
void modioAddFilterInField(ModioFilterHandler* filter, char* field, char* value);
void modioAddFilterNotInField(ModioFilterHandler* filter, char* field, char* value);
void modioAddFilterMinField(ModioFilterHandler* filter, char* field, double value);
void modioAddFilterMaxField(ModioFilterHandler* filter, char* field, double value);
void modioAddFilterSmallerThanField(ModioFilterHandler* filter, char* field, double value);
void modioAddFilterGreaterThanField(ModioFilterHandler* filter, char* field, double value);
void modioAddFilterNotEqualField(ModioFilterHandler* filter, char* field, char* value);
void modioFreeFilter(ModioFilterHandler* filter);

//Modfile Handler Methods
void modioInitModfileHandler(ModioModfileHandler* modfile_handler);
void modioSetModfilePath(ModioModfileHandler* modfile_handler, char* path);
void modioSetModfileVersion(ModioModfileHandler* modfile_handler, char* version);
void modioSetModfileChangelog(ModioModfileHandler* modfile_handler, char* changelog);
void modioSetModfileActive(ModioModfileHandler* modfile_handler, bool active);
void modioDeleteModfileHandler(ModioModfileHandler* modfile_handler);

//Mod Handler Methods
void modioInitModHandler(ModioModHandler* mod_handler);
void modioSetLogoPath(ModioModHandler* mod_handler, char* logo_path);
void modioSetName(ModioModHandler* mod_handler, char* name);
void modioSetHomepage(ModioModHandler* mod_handler, char* homepage);
void modioSetSummary(ModioModHandler* mod_handler, char* summary);
void modioSetPrice(ModioModHandler* mod_handler, double price);
void modioSetStock(ModioModHandler* mod_handler, int stock);
void modioSetDescription(ModioModHandler* mod_handler, char* description);
void modioSetMetadata(ModioModHandler* mod_handler, char* metadata);
void modioSetNameid(ModioModHandler* mod_handler, char* nameid);
void modioSetModfile(ModioModHandler* mod_handler, int modfile);
void modioAddTag(ModioModHandler* mod_handler, char* tag);
void modioFreeModHandler(ModioModHandler* mod_handler);

#define MODIO_DEBUGLEVEL_LOG      2
#define MODIO_DEBUGLEVEL_WARNING  1
#define MODIO_DEBUGLEVEL_ERROR    0

#define MODIO_MODFILE_NOT_INSTALLED 0
#define MODIO_MODFILE_INSTALLED     1
#define MODIO_MODFILE_INSTALLING    2
