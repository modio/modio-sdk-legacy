#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int u32;
typedef int i32;

#define MODIO_ENVIRONMENT_LIVE 0
#define MODIO_ENVIRONMENT_TEST 1

#define MODIO_DEBUGLEVEL_LOG      2
#define MODIO_DEBUGLEVEL_WARNING  1
#define MODIO_DEBUGLEVEL_ERROR    0

#define MODIO_MODFILE_NOT_INSTALLED 0
#define MODIO_MODFILE_INSTALLED     1
#define MODIO_MODFILE_INSTALLING    2

// Status Constants
#define MODIO_NOT_ACCEPTED 0
#define MODIO_ACCEPTED     1
#define MODIO_ARCHIVED     2
#define MODIO_DELETED      3

#define MODIO_HIDDEN 0
#define MODIO_PUBLIC 1

#define MODIO_EVENT_UNDEFINED         0
#define MODIO_EVENT_MODFILE_CHANGED   1
#define MODIO_EVENT_MOD_AVAILABLE     2
#define MODIO_EVENT_MOD_UNAVAILABLE   3
#define MODIO_EVENT_MOD_EDITED        4
#define MODIO_EVENT_USER_TEAM_JOIN    5
#define MODIO_EVENT_USER_TEAM_LEAVE   6
#define MODIO_EVENT_USER_SUBSCRIBE    7
#define MODIO_EVENT_USER_UNSUBSCRIBE  8

// Presentation Option Constants
#define MODIO_GRID_VIEW   0
#define MODIO_TABLE_VIEW  1

// Submission Option Constants
#define MODIO_MOD_UPLOADS_CONTROLED     0
#define MODIO_MOD_UPLOADS_FROM_ANYWHERE 1

// Curation Option Constants
#define MODIO_NO_CURATION   0
#define MODIO_PAID_CURATION 1
#define MODIO_FULL_CURATION 2

#define MODIO_ALL_OPTIONS_DISABLED  0

// Community Options Constants
#define MODIO_DISCUSSION_BOARD_ENABLED  1
#define MODIO_GUIDES_AND_NEWS_ENABLED   2

// Revenue Options Constants
#define MODIO_ALLOW_MODS_TO_BE_SOLD                     1
#define MODIO_ALLOW_MODS_TO_RECEIVE_DONATIONS           2
#define MODIO_ALLOW_MODS_TO_BE_TRADED                   4
#define MODIO_ALLOW_MODS_TO_CONTROL_SUPPLY_AND_SCARCITY 8

// API Access Options Constants
#define MODIO_ALLOW_ACCESS_FROM_3RD_PARTIES         1
#define MODIO_ALLOW_MODS_TO_BE_DOWNLOADED_DIRECTLY  2

// Automatic Updated Options
#define MODIO_UPDATES_DISABLED  0
#define MODIO_UPDATES_ENABLED   1

// Report Types
#define MODIO_GENERIC_REPORT  0
#define MODIO_DMCA_REPORT     1

// Mod states
#define MODIO_MOD_UNDEFINED               0
#define MODIO_MOD_NOT_INSTALLED           1
#define MODIO_MOD_QUEUED                  2
#define MODIO_MOD_STARTING_DOWNLOAD       3
#define MODIO_MOD_DOWNLOADING             4
#define MODIO_MOD_PAUSING                 5
#define MODIO_MOD_PAUSED                  6
#define MODIO_MOD_EXTRACTING              7
#define MODIO_MOD_INSTALLED               8
#define MODIO_PRIORITIZING_OTHER_DOWNLOAD 9
#define MODIO_MOD_STARTING_UPLOAD         10
#define MODIO_MOD_UPLOADING               11

// Maturity options
#define MODIO_MATURITY_NONE     0
#define MODIO_MATURITY_ALCOHOL  1
#define MODIO_MATURITY_DRUGS    2
#define MODIO_MATURITY_VIOLENCE 4
#define MODIO_MATURITY_EXPLICIT 8

typedef struct ModioListNode ModioListNode;
typedef struct ModioAvatar ModioAvatar;
typedef struct ModioComment ModioComment;
typedef struct ModioDependency ModioDependency;
typedef struct ModioError ModioError;
typedef struct ModioFilehash ModioFilehash;
typedef struct ModioGame ModioGame;
typedef struct ModioGameTagOption ModioGameTagOption;
typedef struct ModioHeader ModioHeader;
typedef struct ModioIcon ModioIcon;
typedef struct ModioImage ModioImage;
typedef struct ModioInstalledMod ModioInstalledMod;
typedef struct ModioLogo ModioLogo;
typedef struct ModioMedia ModioMedia;
typedef struct ModioMetadataKVP ModioMetadataKVP;
typedef struct ModioUser ModioUser;
typedef struct ModioDownload ModioDownload;
typedef struct ModioModfile ModioModfile;
typedef struct ModioTag ModioTag;
typedef struct ModioStats ModioStats;
typedef struct ModioMod ModioMod;
typedef struct ModioResponse ModioResponse;
typedef struct ModioFilterCreator ModioFilterCreator;
typedef struct ModioModfileCreator ModioModfileCreator;
typedef struct ModioModfileEditor ModioModfileEditor;
typedef struct ModioModCreator ModioModCreator;
typedef struct ModioModEditor ModioModEditor;
typedef struct ModioEvent ModioEvent;
typedef struct ModioQueuedModDownload ModioQueuedModDownload;
typedef struct ModioQueuedModfileUpload ModioQueuedModfileUpload;

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

struct ModioDependency
{
  u32 mod_id;
  u32 date_added;
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

struct ModioMetadataKVP
{
  char* metakey;
  char* metavalue;
};

struct ModioUser
{
  u32 id;
  u32 date_online;
  char* username;
  char* name_id;
  char* timezone;
  char* language;
  char* profile_url;
  ModioAvatar avatar;
};

struct ModioDownload
{
  char* binary_url;
  u32 date_expires;
};

struct ModioModfile
{
  u32 id;
  u32 mod_id;
  u32 virus_status;
  u32 virus_positive;
  u32 date_added;
  u32 date_scanned;
  long filesize;
  char* filename;
  char* version;
  char* virustotal_hash;
  char* changelog;
  char* metadata_blob;
  ModioFilehash filehash;
  ModioDownload download;
};

struct ModioTag
{
  u32 date_added;
  char* name;
};

struct ModioStats
{
  u32 mod_id;
  u32 popularity_rank_position;
  u32 popularity_rank_total_mods;
  u32 downloads_total;
  u32 subscribers_total;
  u32 ratings_total;
  u32 ratings_positive;
  u32 ratings_negative;
  u32 ratings_percentage_positive;
  double ratings_weighted_aggregate;
  char* ratings_display_text;
  u32 date_expires;
};

struct ModioMod
{
  u32 id;
  u32 game_id;
  u32 status;
  u32 visible;
  u32 maturity_option;
  u32 date_added;
  u32 date_updated;
  u32 date_live;
  char* homepage_url;
  char* name;
  char* name_id;
  char* summary;
  char* description;
  char* description_plaintext;
  char* metadata_blob;
  char* profile_url;
  ModioLogo logo;
  ModioUser submitted_by;
  ModioModfile modfile;
  ModioMedia media;
  ModioStats stats;
  ModioTag* tags_array;
  u32 tags_array_size;
  ModioMetadataKVP* metadata_kvp_array;
  u32 metadata_kvp_array_size;
};

struct ModioResponse
{
  u32 code;
  u32 result_count;
  u32 result_limit;
  i32 result_offset;
  bool result_cached;
  ModioError error;
};

struct ModioFilterCreator
{
  char* sort;
  char* limit;
  char* offset;
  char* full_text_search;
  u32 cache_max_age_seconds;
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
  char* metadata_blob;
  char* active;
  char* filehash;
};

struct ModioModfileEditor
{
  char* version;
  char* changelog;
  char* metadata_blob;
  char* active;
};

struct ModioModCreator
{
  char* visible;
  char* maturity_option;
  char* logo;
  char* name;
  char* name_id;
  char* summary;
  char* description;
  char* homepage_url;
  char* metadata_blob;
  ModioListNode* tags;
};

struct ModioModEditor
{
  char* visible;
  char* status;
  char* maturity_option;
  char* name;
  char* name_id;
  char* summary;
  char* description;
  char* homepage_url;
  char* modfile;
  char* metadata_blob;
};

struct ModioEvent
{
  u32 id;
  u32 mod_id;
  u32 user_id;
  u32 event_type;
  u32 date_added;
};

struct ModioGameTagOption
{
  u32 hidden;
  char* name;
  char* type;
  char** tags_array;
  u32 tags_array_size;
};

struct ModioGame
{
  u32 id;
  u32 status;
  u32 date_added;
  u32 date_updated;
  u32 presentation_option;
  u32 date_live;
  u32 community_options;
  u32 submission_option;
  u32 curation_option;
  u32 revenue_options;
  u32 api_access_options;
  u32 maturity_options;
  char* ugc_name;
  char* instructions_url;
  char* name;
  char* name_id;
  char* summary;
  char* instructions;
  char* profile_url;
  ModioUser submitted_by;
  ModioIcon icon;
  ModioLogo logo;
  ModioHeader header;
  ModioGameTagOption* game_tag_option_array;
  u32 game_tag_option_array_size;
};

struct ModioInstalledMod
{
  u32 mod_id;
  u32 modfile_id;
  u32 updated_at;
  char* path;
  ModioMod mod;
};

struct ModioQueuedModDownload
{
  u32 state;
  u32 mod_id;
  double current_progress;
  double total_size;
  char* url;
  char* path;
  ModioMod mod;
};

struct ModioQueuedModfileUpload
{
  u32 state;
  u32 mod_id;
  double current_progress;
  double total_size;
  char* path;
  ModioModfileCreator modio_modfile_creator;
};

struct ModioComment
{
  u32 id;
  u32 mod_id;
  u32 date_added;
  u32 reply_id;
  u32 karma;
  u32 karma_guest;
  char* thread_position;
  char* content;
  ModioUser user;
};

//General Methods
void modioInit(u32 environment, u32 game_id, char* api_key, char* root_path);
void modioShutdown();
void modioSetDebugLevel(u32 debug_level);
void modioProcess();
void modioSleep(u32 milliseconds);

//Events
void modioSetEventListener(void (*callback)(ModioResponse response, ModioEvent* events_array, u32 events_array_size));
void modioGetEvents(void* object, u32 mod_id, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioEvent* events_array, u32 events_array_size));
void modioGetAllEvents(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioEvent* events_array, u32 events_array_size));

//Authentication methods
void modioEmailRequest(void* object, char* email, void (*callback)(void* object, ModioResponse response));
void modioEmailExchange(void* object, char* security_code, void (*callback)(void* object, ModioResponse response));
bool modioIsLoggedIn();
void modioLogout();

//Image Methods
void modioDownloadImage(void* object, char* image_url, char* path, void (*callback)(void* object, ModioResponse response));

//Modfile Methods
void modioGetModfile(void* object, u32 mod_id, u32 modfile_id, void (*callback)(void* object, ModioResponse response, ModioModfile modfile));
void modioGetAllModfiles(void* object, u32 mod_id, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioModfile modfiles[], u32 modfiles_size));
void modioAddModfile(u32 mod_id, ModioModfileCreator modfile_creator);
void modioEditModfile(void* object, u32 mod_id, u32 modfile_id, ModioModfileEditor modfile_handler, void (*callback)(void* object, ModioResponse response, ModioModfile modfile));

//Mods Methods
void modioGetMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioMod mod));
void modioGetAllMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size));
void modioAddMod(void* object, ModioModCreator mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod mod));
void modioEditMod(void* object, u32 mod_id, ModioModEditor mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod mod));
void modioDeleteMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response));

//Media Methods
void modioAddModLogo(void* object, u32 mod_id, char* logo_path, void (*callback)(void* object, ModioResponse response));
void modioAddModImages(void* object, u32 mod_id, char** image_paths_array, u32 image_paths_array_size, void (*callback)(void* object, ModioResponse response));
void modioAddModYoutubeLinks(void* object, u32 mod_id, char** youtube_links_array, u32 youtube_links_array_size, void (*callback)(void* object, ModioResponse response));
void modioAddModSketchfabLinks(void* object, u32 mod_id, char** sketchfab_links_array, u32 sketchfab_links_array_size, void (*callback)(void* object, ModioResponse response));
void modioDeleteModImages(void* object, u32 mod_id, char** image_paths_array, u32 image_paths_array_size, void (*callback)(void* object, ModioResponse response));
void modioDeleteModYoutubeLinks(void* object, u32 mod_id, char** youtube_links_array, u32 youtube_links_array_size, void (*callback)(void* object, ModioResponse response));
void modioDeleteModSketchfabLinks(void* object, u32 mod_id, char** sketchfab_links_array, u32 sketchfab_links_array_size, void (*callback)(void* object, ModioResponse response));

//Ratings Methods
void modioAddModRating(void* object, u32 mod_id, bool vote_up, void (*callback)(void* object, ModioResponse response));

//Subscription Methods
void modioSubscribeToMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioMod mod));
void modioUnsubscribeFromMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response));

//Tags Methods
void modioGetModTags(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioTag* tags_array, u32 tags_array_size));
void modioAddModTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response));
void modioDeleteModTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response));

//Metadata KVP Methods
void modioGetAllMetadataKVP(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioMetadataKVP* metadata_kvp_array, u32 metadata_kvp_array_size));
void modioAddMetadataKVP(void* object, u32 mod_id, char** metadata_kvp_array, u32 metadata_kvp_array_size, void (*callback)(void* object, ModioResponse response));
void modioDeleteMetadataKVP(void* object, u32 mod_id, char** metadata_kvp_array, u32 metadata_kvp_array_size, void (*callback)(void* object, ModioResponse response));

//Filter Handler Methods
void modioInitFilter(ModioFilterCreator* filter);
void modioSetFilterSort(ModioFilterCreator* filter, char* field, bool ascending);
void modioSetFilterLimit(ModioFilterCreator* filter, u32 limit);
void modioSetFilterOffset(ModioFilterCreator* filter, u32 offset);
void modioSetFilterFullTextSearch(ModioFilterCreator* filter, char* text);
void modioSetFilterCacheMaxAgeSeconds(ModioFilterCreator* filter, u32 max_age_seconds);
void modioAddFilterFieldValue(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterLikeField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterNotLikeField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterInField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterNotInField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterMinField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterMaxField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterSmallerThanField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterGreaterThanField(ModioFilterCreator* filter, char* field, char* value);
void modioAddFilterNotEqualField(ModioFilterCreator* filter, char* field, char* value);
void modioFreeFilter(ModioFilterCreator* filter);

//Modfile Creator Methods
void modioInitModfileCreator(ModioModfileCreator* modfile_creator);
void modioSetModfileCreatorPath(ModioModfileCreator* modfile_creator, char* path);
void modioSetModfileCreatorVersion(ModioModfileCreator* modfile_creator, char* version);
void modioSetModfileCreatorChangelog(ModioModfileCreator* modfile_creator, char* changelog);
void modioSetModfileCreatorMetadataBlob(ModioModfileCreator* modfile_creator, char* metadata_blob);
void modioSetModfileCreatorActive(ModioModfileCreator* modfile_creator, bool active);
void modioSetModfileCreatorFilehash(ModioModfileCreator* modfile_creator, char* filehash);
void modioFreeModfileCreator(ModioModfileCreator* modfile_creator);

//Modfile Editor Methods
void modioInitModfileEditor(ModioModfileEditor* modfile_creator);
void modioSetModfileEditorVersion(ModioModfileEditor* modfile_creator, char* version);
void modioSetModfileEditorChangelog(ModioModfileEditor* modfile_creator, char* changelog);
void modioSetModfileEditorMetadataBlob(ModioModfileEditor* modfile_creator, char* metadata_blob);
void modioSetModfileEditorActive(ModioModfileEditor* modfile_creator, bool active);
void modioFreeModfileEditor(ModioModfileEditor* modfile_creator);

//Mod Creator Methods
void modioInitModCreator(ModioModCreator* mod_creator);
void modioSetModCreatorVisible(ModioModCreator* mod_creator, u32 visible);
void modioSetModCreatorMaturityOption(ModioModCreator* mod_creator, u32 maturity_option);
void modioSetModCreatorLogoPath(ModioModCreator* mod_creator, char* logo_path);
void modioSetModCreatorName(ModioModCreator* mod_creator, char* name);
void modioSetModCreatorNameid(ModioModCreator* mod_creator, char* name_id);
void modioSetModCreatorSummary(ModioModCreator* mod_creator, char* summary);
void modioSetModCreatorDescription(ModioModCreator* mod_creator, char* description);
void modioSetModCreatorHomepageURL(ModioModCreator* mod_creator, char* homepage_url);
void modioSetModCreatorMetadataBlob(ModioModCreator* mod_creator, char* metadata_blob);
void modioAddModCreatorTag(ModioModCreator* mod_creator, char* tag);
void modioFreeModCreator(ModioModCreator* mod_creator);

//Mod Editor Methods
void modioInitModEditor(ModioModEditor* update_mod_handler);
void modioSetModEditorVisible(ModioModEditor* update_mod_handler, u32 visible);
void modioSetModEditorStatus(ModioModEditor* update_mod_handler, u32 status);
void modioSetModEditorMaturityOption(ModioModEditor* mod_editor, u32 maturity_option);
void modioSetModEditorName(ModioModEditor* update_mod_handler, char* name);
void modioSetModEditorNameid(ModioModEditor* update_mod_handler, char* name_id);
void modioSetModEditorSummary(ModioModEditor* update_mod_handler, char* summary);
void modioSetModEditorDescription(ModioModEditor* update_mod_handler, char* description);
void modioSetModEditorHomepageURL(ModioModEditor* update_mod_handler, char* homepage_url);
void modioSetModEditorModfile(ModioModEditor* update_mod_handler, u32 modfile);
void modioSetModEditorMetadataBlob(ModioModEditor* update_mod_handler, char* metadata_blob);
void modioFreeModEditor(ModioModEditor* update_mod_handler);

//Me Methods
void modioGetAuthenticatedUser(void* object, void (*callback)(void* object, ModioResponse response, ModioUser user));
void modioGetUserSubscriptions(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size));
void modioGetUserEvents(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioEvent* events_array, u32 events_array_size));
void modioGetUserGames(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioGame games[], u32 games_size));
void modioGetUserMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size));
void modioGetUserModfiles(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioModfile modfiles[], u32 modfiles_size));

//Settings Methods
void modioInitConfig();
u32 modioGetAutomaticUpdatesConfig();
u32 modioGetAllowBackgroundDownloadsConfig();
void modioSetAutomaticUpdatesConfig(u32 option);
void modioSetAllowBackgroundDownloadsConfig(u32 option);

//Downloads Methods
void modioInstallMod(u32 mod_id);
bool modioUninstallMod(u32 mod_id);
void modioPauseDownloads();
void modioResumeDownloads();
void modioPrioritizeModDownload(u32 mod_id);
void modioSetDownloadListener(void (*callback)(u32 response_code, u32 mod_id));  
void modioSetUploadListener(void (*callback)(u32 response_code, u32 mod_id));  
u32 modioGetModDownloadQueueCount();
void modioGetModDownloadQueue(ModioQueuedModDownload* download_queue);
u32 modioGetModfileUploadQueueCount();
void modioGetModfileUploadQueue(ModioQueuedModfileUpload* upload_queue);
u32 modioGetAllInstalledModsCount();
void modioGetAllInstalledMods(ModioInstalledMod* installed_mods);
bool modioGetAllInstalledModById(u32 mod_id, ModioInstalledMod *installed_mod);  
u32 modioGetModState(u32 mod_id);

//Dependencies Methods
void modioGetAllModDependencies(void* object, u32 mod_id, void(*callback)(void* object, ModioResponse response, ModioDependency* dependencies_array, u32 dependencies_array_size));
void modioAddModDependencies(void* object, u32 mod_id, u32* dependencies_array, u32 dependencies_array_size, void(*callback)(void* object, ModioResponse response));
void modioDeleteModDependencies(void* object, u32 mod_id, u32* dependencies_array, u32 dependencies_array_size, void(*callback)(void* object, ModioResponse response));

//Comment Methods
void modioGetAllModComments(void* object, u32 mod_id, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioComment comments[], u32 comments_size));
void modioGetModComment(void* object, u32 mod_id, u32 comment_id, void (*callback)(void* object, ModioResponse response, ModioComment comment));  
void modioDeleteModComment(void* object, u32 mod_id, u32 comment_id, void(*callback)(void* object, ModioResponse response));

//Reports Methods
void modioSubmitReport(void* object, char* resource, u32 id, u32 type, char* name, char* summary, void(*callback)(void* object, ModioResponse response));

//Stats Methods
void modioGetModStats(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioStats mod));
void modioGetAllModStats(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioStats mods_stats[], u32 mods_stats_size));