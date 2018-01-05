#ifndef MODIO_STRUCTS_H
#define MODIO_STRUCTS_H

extern "C"
{
  struct ModioListNode;

  struct ModioListNode
  {
    char* value;
    ModioListNode* next;
  };

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
    char* filehash;
  }ModioModfileCreator;

  typedef struct
  {
    char* version;
    char* changelog;
    char* active;
  }ModioModfileUpdater;

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
  }ModioModUpdater;

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
  void MODIO_DLL modioAddModfile(void* object, u32 mod_id, ModioModfileCreator modfile_handler, void (*callback)(void* object, ModioResponse response, ModioModfile modfile));
  void MODIO_DLL modioEditModfile(void* object, u32 mod_id, u32 modfile_id, ModioModfileUpdater modfile_handler, void (*callback)(void* object, ModioResponse response, ModioModfile modfile));
  void MODIO_DLL modioInstallModfile(void* object, u32 modfile_id, char* modfile_download, char* destination_path, void (*callback)(void* object, ModioResponse response));
  u32 MODIO_DLL modioGetModfileState(u32 modfile_id);
  double MODIO_DLL modioGetModfileDownloadPercentage(u32 modfile_id);
  bool MODIO_DLL modioUninstallModfile(u32 modfile_id);
  u32 MODIO_DLL modioGetInstalledModfilesCount();
  u32 MODIO_DLL modioGetInstalledModfileId(u32 index);

  //Mods Methods
  void MODIO_DLL modioGetMods(void* object, ModioFilterHandler filter, void (*callback)(void* object, ModioResponse response, ModioMod mods[], u32 mods_size));
  void MODIO_DLL modioAddMod(void* object, ModioModCreator mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod mod));
  void MODIO_DLL modioEditMod(void* object, u32 mod_id, ModioModUpdater mod_handler, void (*callback)(void* object, ModioResponse response, ModioMod mod));
  void MODIO_DLL modioDeleteMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));
  void MODIO_DLL modioSetUserModVote(void* object, u32 mod_id, bool vote_up, void (*callback)(void* object, ModioResponse response, u32 mod_id));
  void MODIO_DLL modioSubscribeMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));
  void MODIO_DLL modioUnsubscribeMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id));

  //Tags Methods
  void MODIO_DLL modioGetTags(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, u32 mod_id, ModioTag* tags_array, u32 tags_array_size));
  void MODIO_DLL modioAddTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response, u32 mod_id));
  void MODIO_DLL modioDeleteTags(void* object, u32 mod_id, char** tags_array, u32 tags_array_size, void (*callback)(void* object, ModioResponse response, u32 mod_id));

  //Filter Handler Methods
  void MODIO_DLL modioInitFilter(ModioFilterHandler* filter);
  void MODIO_DLL modioSetFilterSort(ModioFilterHandler* filter, char* field, bool ascending);
  void MODIO_DLL modioSetFilterLimit(ModioFilterHandler* filter, u32 limit);
  void MODIO_DLL modioSetFilterOffset(ModioFilterHandler* filter, u32 offset);
  void MODIO_DLL modioSetFilterFullTextSearch(ModioFilterHandler* filter, char* text);
  void MODIO_DLL modioAddFilterFieldValue(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterLikeField(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterNotLikeField(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterInField(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterNotInField(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterMinField(ModioFilterHandler* filter, char* field, double value);
  void MODIO_DLL modioAddFilterMaxField(ModioFilterHandler* filter, char* field, double value);
  void MODIO_DLL modioAddFilterSmallerThanField(ModioFilterHandler* filter, char* field, double value);
  void MODIO_DLL modioAddFilterGreaterThanField(ModioFilterHandler* filter, char* field, double value);
  void MODIO_DLL modioAddFilterNotEqualField(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioFreeFilter(ModioFilterHandler* filter);

  //Modfile Creator Handler Methods
  void MODIO_DLL modioInitModfileCreator(ModioModfileCreator* modfile_creator);
  void MODIO_DLL modioSetModfileCreatorPath(ModioModfileCreator* modfile_creator, char* path);
  void MODIO_DLL modioSetModfileCreatorVersion(ModioModfileCreator* modfile_creator, char* version);
  void MODIO_DLL modioSetModfileCreatorChangelog(ModioModfileCreator* modfile_creator, char* changelog);
  void MODIO_DLL modioSetModfileCreatorActive(ModioModfileCreator* modfile_creator, bool active);
  void MODIO_DLL modioSetModfileCreatorFilehash(ModioModfileCreator* modfile_creator, char* filehash);
  void MODIO_DLL modioFreeModfileCreator(ModioModfileCreator* modfile_creator);

  //Update Modfile Handler Methods
  void MODIO_DLL modioInitModfileUpdater(ModioModfileUpdater* modfile_creator);
  void MODIO_DLL modioSetModfileUpdaterVersion(ModioModfileUpdater* modfile_creator, char* version);
  void MODIO_DLL modioSetModfileUpdaterChangelog(ModioModfileUpdater* modfile_creator, char* changelog);
  void MODIO_DLL modioSetModfileUpdaterActive(ModioModfileUpdater* modfile_creator, bool active);
  void MODIO_DLL modioFreeModfileUpdater(ModioModfileUpdater* modfile_creator);

  //Add Mod Handler Methods
  void MODIO_DLL modioInitModCreator(ModioModCreator* mod_creator);
  void MODIO_DLL modioSetModCreatorLogoPath(ModioModCreator* mod_creator, char* logo_path);
  void MODIO_DLL modioSetModCreatorName(ModioModCreator* mod_creator, char* name);
  void MODIO_DLL modioSetModCreatorNameid(ModioModCreator* mod_creator, char* name_id);
  void MODIO_DLL modioSetModCreatorSummary(ModioModCreator* mod_creator, char* summary);
  void MODIO_DLL modioSetModCreatorDescription(ModioModCreator* mod_creator, char* description);
  void MODIO_DLL modioSetModCreatorHomepage(ModioModCreator* mod_creator, char* homepage);
  void MODIO_DLL modioSetModCreatorMetadataBlob(ModioModCreator* mod_creator, char* metadata_blob);
  void MODIO_DLL modioAddModCreatorTag(ModioModCreator* mod_creator, char* tag);
  void MODIO_DLL modioFreeModCreator(ModioModCreator* mod_creator);

  //Update Mod Handler Methods
  void MODIO_DLL modioInitModUpdater(ModioModUpdater* update_mod_handler);
  void MODIO_DLL modioSetModUpdaterName(ModioModUpdater* update_mod_handler, char* name);
  void MODIO_DLL modioSetModUpdaterNameid(ModioModUpdater* update_mod_handler, char* name_id);
  void MODIO_DLL modioSetModUpdaterSummary(ModioModUpdater* update_mod_handler, char* summary);
  void MODIO_DLL modioSetModUpdaterDescription(ModioModUpdater* update_mod_handler, char* description);
  void MODIO_DLL modioSetModUpdaterHomepage(ModioModUpdater* update_mod_handler, char* homepage);
  void MODIO_DLL modioSetModUpdaterModfile(ModioModUpdater* update_mod_handler, u32 modfile);
  void MODIO_DLL modioSetModUpdaterMetadataBlob(ModioModUpdater* update_mod_handler, char* metadata_blob);
  void MODIO_DLL modioSetModUpdaterStatus(ModioModUpdater* update_mod_handler, char* status);
  void MODIO_DLL modioFreeModUpdater(ModioModUpdater* update_mod_handler);
}

#endif
