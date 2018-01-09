#ifndef MODIO_MODIO_C_H
#define MODIO_MODIO_C_H

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

extern "C"
{
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
  };

  //General Methods
  void MODIO_DLL modioInit(u32 game_id, char* api_key);
  //void MODIO_DLL init(int game_id, char* api_key, char* root_path);
  void MODIO_DLL modioShutdown();
  //CurrentDownloadInfo MODIO_DLL modioGetCurrentDownloadInfo();
  void MODIO_DLL modioPauseCurrentDownload();
  void MODIO_DLL modioSetDebugLevel(u32 debug_level);
  void MODIO_DLL modioProcess();
  void MODIO_DLL modioSleep(u32 milliseconds);

  //Authentication methods
  void MODIO_DLL modioEmailRequest(void* object, char* email, void (*callback)(void* object, ModioResponse response));
  void MODIO_DLL modioEmailExchange(void* object, char* security_code, void (*callback)(void* object, ModioResponse response));
  bool MODIO_DLL modioIsLoggedIn();
  void MODIO_DLL modioLogout();

  //Image Methods
  void MODIO_DLL modioDownloadImage(void* object, char* image_url, char* path, void (*callback)(void* object, ModioResponse response));
  void MODIO_DLL modioEditModLogo(void* object, u32 mod_id, char* path, void (*callback)(void* object, ModioResponse response, u32 mod_id));

  //Modfile Methods
  void MODIO_DLL modioAddModfile(void* object, u32 mod_id, ModioModfileCreator modfile_creator, void (*callback)(void* object, ModioResponse response, ModioModfile modfile));
  void MODIO_DLL modioEditModfile(void* object, u32 mod_id, u32 modfile_id, ModioModfileEditor modfile_handler, void (*callback)(void* object, ModioResponse response, ModioModfile modfile));
  void MODIO_DLL modioInstallModfile(void* object, u32 modfile_id, char* modfile_download, char* destination_path, void (*callback)(void* object, ModioResponse response));
  u32 MODIO_DLL modioGetModfileState(u32 modfile_id);
  double MODIO_DLL modioGetModfileDownloadPercentage(u32 modfile_id);
  bool MODIO_DLL modioUninstallModfile(u32 modfile_id);
  u32 MODIO_DLL modioGetInstalledModfilesCount();
  u32 MODIO_DLL modioGetInstalledModfileId(u32 index);

  //Mods Methods
  void MODIO_DLL modioGetMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioMod mod));
  void MODIO_DLL modioGetMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size));
  void MODIO_DLL modioGetUserMods(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size));
  void MODIO_DLL modioAddMod(void* object, ModioModCreator mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod mod));
  void MODIO_DLL modioEditMod(void* object, u32 mod_id, ModioModEditor mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod mod));
  void MODIO_DLL modioDeleteMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));
  void MODIO_DLL modioSetUserModVote(void* object, u32 mod_id, bool vote_up, void (*callback)(void* object, ModioResponse response, u32 mod_id));
  void MODIO_DLL modioSubscribeMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));
  void MODIO_DLL modioUnsubscribeMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));

  //Tags Methods
  void MODIO_DLL modioGetTags(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id, ModioTag* tags_array, u32 tags_array_size));
  void MODIO_DLL modioAddTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response, u32 mod_id));
  void MODIO_DLL modioDeleteTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response, u32 mod_id));

  //Filter Handler Methods
  void MODIO_DLL modioInitFilter(ModioFilterCreator* filter);
  void MODIO_DLL modioSetFilterSort(ModioFilterCreator* filter, char* field, bool ascending);
  void MODIO_DLL modioSetFilterLimit(ModioFilterCreator* filter, u32 limit);
  void MODIO_DLL modioSetFilterOffset(ModioFilterCreator* filter, u32 offset);
  void MODIO_DLL modioSetFilterFullTextSearch(ModioFilterCreator* filter, char* text);
  void MODIO_DLL modioAddFilterFieldValue(ModioFilterCreator* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterLikeField(ModioFilterCreator* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterNotLikeField(ModioFilterCreator* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterInField(ModioFilterCreator* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterNotInField(ModioFilterCreator* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterMinField(ModioFilterCreator* filter, char* field, double value);
  void MODIO_DLL modioAddFilterMaxField(ModioFilterCreator* filter, char* field, double value);
  void MODIO_DLL modioAddFilterSmallerThanField(ModioFilterCreator* filter, char* field, double value);
  void MODIO_DLL modioAddFilterGreaterThanField(ModioFilterCreator* filter, char* field, double value);
  void MODIO_DLL modioAddFilterNotEqualField(ModioFilterCreator* filter, char* field, char* value);
  void MODIO_DLL modioFreeFilter(ModioFilterCreator* filter);

  //Modfile Creator Methods
  void MODIO_DLL modioInitModfileCreator(ModioModfileCreator* modfile_creator);
  void MODIO_DLL modioSetModfileCreatorPath(ModioModfileCreator* modfile_creator, char* path);
  void MODIO_DLL modioSetModfileCreatorVersion(ModioModfileCreator* modfile_creator, char* version);
  void MODIO_DLL modioSetModfileCreatorChangelog(ModioModfileCreator* modfile_creator, char* changelog);
  void MODIO_DLL modioSetModfileCreatorActive(ModioModfileCreator* modfile_creator, bool active);
  void MODIO_DLL modioSetModfileCreatorFilehash(ModioModfileCreator* modfile_creator, char* filehash);
  void MODIO_DLL modioFreeModfileCreator(ModioModfileCreator* modfile_creator);

  //Modfile Editor Methods
  void MODIO_DLL modioInitModfileEditor(ModioModfileEditor* modfile_creator);
  void MODIO_DLL modioSetModfileEditorVersion(ModioModfileEditor* modfile_creator, char* version);
  void MODIO_DLL modioSetModfileEditorChangelog(ModioModfileEditor* modfile_creator, char* changelog);
  void MODIO_DLL modioSetModfileEditorActive(ModioModfileEditor* modfile_creator, bool active);
  void MODIO_DLL modioFreeModfileEditor(ModioModfileEditor* modfile_creator);

  //Mod Creator Methods
  void MODIO_DLL modioInitModCreator(ModioModCreator* mod_creator);
  void MODIO_DLL modioSetModCreatorVisible(ModioModCreator* mod_creator, u32 visible);
  void MODIO_DLL modioSetModCreatorLogoPath(ModioModCreator* mod_creator, char* logo_path);
  void MODIO_DLL modioSetModCreatorName(ModioModCreator* mod_creator, char* name);
  void MODIO_DLL modioSetModCreatorNameid(ModioModCreator* mod_creator, char* name_id);
  void MODIO_DLL modioSetModCreatorSummary(ModioModCreator* mod_creator, char* summary);
  void MODIO_DLL modioSetModCreatorDescription(ModioModCreator* mod_creator, char* description);
  void MODIO_DLL modioSetModCreatorHomepage(ModioModCreator* mod_creator, char* homepage);
  void MODIO_DLL modioSetModCreatorMetadataBlob(ModioModCreator* mod_creator, char* metadata_blob);
  void MODIO_DLL modioAddModCreatorTag(ModioModCreator* mod_creator, char* tag);
  void MODIO_DLL modioFreeModCreator(ModioModCreator* mod_creator);

  //Mod Editor Methods
  void MODIO_DLL modioInitModEditor(ModioModEditor* update_mod_handler);
  void MODIO_DLL modioSetModEditorVisible(ModioModEditor* update_mod_handler, u32 visible);
  void MODIO_DLL modioSetModEditorStatus(ModioModEditor* update_mod_handler, u32 status);
  void MODIO_DLL modioSetModEditorName(ModioModEditor* update_mod_handler, char* name);
  void MODIO_DLL modioSetModEditorNameid(ModioModEditor* update_mod_handler, char* name_id);
  void MODIO_DLL modioSetModEditorSummary(ModioModEditor* update_mod_handler, char* summary);
  void MODIO_DLL modioSetModEditorDescription(ModioModEditor* update_mod_handler, char* description);
  void MODIO_DLL modioSetModEditorHomepage(ModioModEditor* update_mod_handler, char* homepage);
  void MODIO_DLL modioSetModEditorModfile(ModioModEditor* update_mod_handler, u32 modfile);
  void MODIO_DLL modioSetModEditorMetadataBlob(ModioModEditor* update_mod_handler, char* metadata_blob);
  void MODIO_DLL modioFreeModEditor(ModioModEditor* update_mod_handler);
}

#endif
