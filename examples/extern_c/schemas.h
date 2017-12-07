#include<stdio.h>
#include <stdbool.h>

typedef unsigned int u32;

typedef struct
{
  u32 code;
  char* message;
  char** errors_array;
  u32 errors_array_size;
}ModioError;

typedef struct
{
  u32 code;
  u32 cursor_id;
  u32 prev_id;
  u32 next_id;
  u32 result_count;
  ModioError error;
}ModioResponse;

typedef struct
{
  char* filename;
  char* original;
  char* thumb_320x180;
  char* thumb_640x360;
  char* thumb_1280x720;
}ModioImage;

typedef struct
{
  u32 id;
  long date_online;
  char* username;
  char* name_id;
  char* timezone;
  char* language;
  char* profile_url;
  ModioImage avatar;
}ModioUser;

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
  char* md5;
}ModioFilehash;

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
  ModioImage logo;
  ModioUser submitted_by;
  ModioMedia media;
  ModioModfile modfile;
  ModioRatingSummary rating_summary;
  ModioTag* tags_array;
  u32 tags_array_size;
}ModioMod;

typedef struct
{
  char* value;
  struct ModioListNode* next;
}ModioListNode;

typedef struct
{
  char* sort;
  char* limit;
  char* offset;
  char* cursor;
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
