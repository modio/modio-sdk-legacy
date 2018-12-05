#include "json_examples.h"

nlohmann::json message_json = R"(
{
  "code": 200,
  "message": "Your request was successful."
} 
)"_json;

nlohmann::json error_json = R"(
{
  "error": {
    "code": 403,
    "message": "You do not have the required permissions to access this resource.",
    "errors": {}
  }
} 
)"_json;

nlohmann::json logo_json = R"(
{
  "filename": "modio-color-dark.png",
  "original": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
  "thumb_320x180": "https://static.mod.io/v1/images/thumb_320x180.png",
  "thumb_640x360": "https://static.mod.io/v1/images/thumb_640x360.png",
  "thumb_1280x720": "https://static.mod.io/v1/images/thumb_1280x720.png"
} 
)"_json;

nlohmann::json icon_json = R"(
{
  "filename": "modio-color-dark.png",
  "original": "https://static.mod.io/v1/images/original.png",
  "thumb_64x64": "https://static.mod.io/v1/images/thumb_64x64.png",
  "thumb_128x128": "https://static.mod.io/v1/images/thumb_128x128.png",
  "thumb_256x256": "https://static.mod.io/v1/images/thumb_256x256.png"
} 
)"_json;

nlohmann::json header_image_json = R"(
{
  "filename": "demo.png",
  "original": "https://static.mod.io/v1/images/original.png"
} 
)"_json;

nlohmann::json avatar_json = R"(
{
  "filename": "modio-color-dark.png",
  "original": "https://static.mod.io/v1/images/original.png",
  "thumb_50x50": "https://static.mod.io/v1/images/thumb_50x50.png",
  "thumb_100x100": "https://static.mod.io/v1/images/thumb_100x100.png"
} 
)"_json;

nlohmann::json image_json = R"(
{
  "filename": "modio-color-dark.png",
  "original": "https://static.mod.io/v1/images/original.png",
  "thumb_320x180": "https://static.mod.io/v1/images/thumb_320x180.png"
} 
)"_json;

nlohmann::json event_json = R"(
{
  "id": 13,
  "mod_id": 14,
  "user_id": 15,
  "date_added": 1499846132,
  "event_type": "MODFILE_CHANGED"
} 
)"_json;

nlohmann::json comment_json = R"(
{
  "id": 2,
  "mod_id": 3,
  "user": {
    "id": 1,
    "name_id": "xant",
    "username": "XanT",
    "date_online": 1509922961,
    "avatar": {
      "filename": "modio-color-dark.png",
      "original": "https://static.mod.io/v1/images/original.png",
      "thumb_50x50": "https://static.mod.io/v1/images/thumb_50x50.png",
      "thumb_100x100": "https://static.mod.io/v1/images/thumb_100x100.png"
    },
    "timezone": "America/Los_Angeles",
    "language": "en",
    "profile_url": "https://mod.io/members/xant"
  },
  "date_added": 1499841487,
  "reply_id": 1499,
  "thread_position": "01",
  "karma": 1,
  "karma_guest": 0,
  "content": "This mod is kickass! Great work!"
} 
)"_json;

nlohmann::json mod_dependency_json = R"(
{
  "mod_id": 231,
  "date_added": 1499841487
} 
)"_json;

nlohmann::json game_tag_option_json = R"(
{
  "name": "Theme",
  "type": "checkboxes",
  "tags": [
    "Horror"
  ],
  "hidden": false
} 
)"_json;

nlohmann::json modfile_json = R"(
{
  "id": 2,
  "mod_id": 3,
  "date_added": 1499841487,
  "date_scanned": 1499841487,
  "virus_status": 5,
  "virus_positive": 1,
  "virustotal_hash": "f9a7bf4a95ce20787337b685a79677cae2281b83c63ab0a25f091407741692af-1508147401",
  "filesize": 15181,
  "filehash": {
    "md5": "2d4a0e2d7273db6b0a94b0740a88ad0d"
  },
  "filename": "rogue-knight-v1.zip",
  "version": "1.3",
  "changelog": "VERSION 1.3 -- Changes -- Fixed critical castle floor bug.",
  "metadata_blob": "rogue,hd,high-res,4k,hd textures",
  "download": {
    "binary_url": "https://mod.io/mods/file/1/c489a0354111a4d76640d47f0cdcb294",
    "date_expires": 1579316848
  }
} 
)"_json;

nlohmann::json filehash_json = R"(
{
  "md5": "2d4a0e2d7273db6b0a94b0740a88ad0d"
} 
)"_json;

nlohmann::json download_json = R"(
{
  "binary_url": "https://mod.io/mods/file/1/c489a0354111a4d76640d47f0cdcb294",
  "date_expires": 1579316848
} 
)"_json;

nlohmann::json mod_media_json = R"(
{
  "youtube": [
    "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
  ],
  "sketchfab": [
    "https://sketchfab.com/models/ef40b2d300334d009984c8865b2db1c8"
  ],
  "images": [
    {
      "filename": "modio-color-dark.png",
      "original": "https://static.mod.io/v1/images/original.png",
      "thumb_320x180": "https://static.mod.io/v1/images/thumb_320x180.png"
    }
  ]
} 
)"_json;

nlohmann::json mod_tag_json = R"(
{
  "name": "Unity",
  "date_added": 1499841487
} 
)"_json;

nlohmann::json metadata_kvp_json = R"(
{
  "metakey": "pistol-dmg",
  "metavalue": "800"
} 
)"_json;

nlohmann::json rating_json = R"(
{
  "game_id": 2,
  "mod_id": 3,
  "rating": -1,
  "date_added": 1492564103
} 
)"_json;

nlohmann::json stats_json = R"(
{
  "mod_id": 2,
  "popularity_rank_position": 13,
  "popularity_rank_total_mods": 204,
  "downloads_total": 27492,
  "subscribers_total": 16394,
  "ratings_total": 1230,
  "ratings_positive": 1047,
  "ratings_negative": 183,
  "ratings_percentage_positive": 91,
  "ratings_weighted_aggregate": 87.38,
  "ratings_display_text": "Very Positive",
  "date_expires": 1492564103
} 
)"_json;

nlohmann::json team_member_json = R"(
{
  "id": 457,
  "user": {
    "id": 1,
    "name_id": "xant",
    "username": "XanT",
    "date_online": 1509922961,
    "avatar": {
      "filename": "modio-color-dark.png",
      "original": "https://static.mod.io/v1/images/original.png",
      "thumb_50x50": "https://static.mod.io/v1/images/thumb_50x50.png",
      "thumb_100x100": "https://static.mod.io/v1/images/thumb_100x100.png"
    },
    "timezone": "America/Los_Angeles",
    "language": "en",
    "profile_url": "https://mod.io/members/xant"
  },
  "level": 8,
  "date_added": 1492058857,
  "position": "Supreme Overlord"
} 
)"_json;

nlohmann::json user_json = R"(
{
  "id": 1,
  "name_id": "xant",
  "username": "XanT",
  "date_online": 1509922961,
  "avatar": {
    "filename": "modio-color-dark.png",
    "original": "https://static.mod.io/v1/images/original.png",
    "thumb_50x50": "https://static.mod.io/v1/images/thumb_50x50.png",
    "thumb_100x100": "https://static.mod.io/v1/images/thumb_100x100.png"
  },
  "timezone": "America/Los_Angeles",
  "language": "en",
  "profile_url": "https://mod.io/members/xant"
} 
)"_json;

nlohmann::json game_json = R"(
{
  "id": 2,
  "status": 1,
  "submitted_by": {
    "id": 1,
    "name_id": "xant",
    "username": "XanT",
    "date_online": 1509922961,
    "avatar": {
      "filename": "modio-color-dark.png",
      "original": "https://static.mod.io/v1/images/original.png",
      "thumb_50x50": "https://static.mod.io/v1/images/thumb_50x50.png",
      "thumb_100x100": "https://static.mod.io/v1/images/thumb_100x100.png"
    },
    "timezone": "America/Los_Angeles",
    "language": "en",
    "profile_url": "https://mod.io/members/xant"
  },
  "date_added": 1493702614,
  "date_updated": 1499410290,
  "date_live": 1499841403,
  "presentation_option": 1,
  "submission_option": 0,
  "curation_option": 0,
  "community_options": 3,
  "revenue_options": 1500,
  "api_access_options": 3,
  "maturity_options": 0,
  "ugc_name": "map",
  "icon": {
    "filename": "modio-color-dark.png",
    "original": "https://static.mod.io/v1/images/original.png",
    "thumb_64x64": "https://static.mod.io/v1/images/thumb_64x64.png",
    "thumb_128x128": "https://static.mod.io/v1/images/thumb_128x128.png",
    "thumb_256x256": "https://static.mod.io/v1/images/thumb_256x256.png"
  },
  "logo": {
    "filename": "modio-color-dark.png",
    "original": "https://static.mod.io/v1/images/original.png",
    "thumb_320x180": "https://static.mod.io/v1/images/thumb_320x180.png",
    "thumb_640x360": "https://static.mod.io/v1/images/thumb_640x360.png",
    "thumb_1280x720": "https://static.mod.io/v1/images/thumb_1280x720.png"
  },
  "header": {
    "filename": "demo.png",
    "original": "https://static.mod.io/v1/images/original.png"
  },
  "name": "Rogue Knight",
  "name_id": "rogue-knight",
  "summary": "Rogue Knight is a brand new 2D pixel platformer.",
  "instructions": "Instructions on the process to upload mods.",
  "instructions_url": "https://www.rogue-knight-game.com/modding/getting-started",
  "profile_url": "https://rogue-knight.mod.io",
  "tag_options": [
    {
      "name": "Theme",
      "type": "checkboxes",
      "tags": [
        "Horror"
      ],
      "hidden": false
    }
  ]
} 
)"_json;

nlohmann::json mod_json = R"(
	{
		"id": 2,
		"game_id": 2,
		"status": 1,
		"visible": 1,
		"submitted_by": {
			"id": 1,
			"name_id": "xant",
			"username": "XanT",
			"date_online": 1509922961,
			"avatar": {
				"filename": "modio-color-dark.png",
				"original": "https://static.mod.io/v1/images/original.png",
				"thumb_50x50": "https://static.mod.io/v1/images/thumb_50x50.png",
				"thumb_100x100": "https://static.mod.io/v1/images/thumb_100x100.png"
			},
			"timezone": "America/Los_Angeles",
			"language": "en",
			"profile_url": "https://mod.io/members/xant"
		},
		"date_added": 1492564103,
		"date_updated": 1499841487,
		"date_live": 1499841403,
		"maturity_option": 0,
		"logo": {
			"filename": "modio-color-dark.png",
			"original": "https://static.mod.io/v1/images/original.png",
			"thumb_320x180": "https://static.mod.io/v1/images/thumb_320x180.png",
			"thumb_640x360": "https://static.mod.io/v1/images/thumb_640x360.png",
			"thumb_1280x720": "https://static.mod.io/v1/images/thumb_1280x720.png"
		},
		"homepage_url": "https://www.rogue-hdpack.com/",
		"name": "Rogue Knight HD Pack",
		"name_id": "rogue-knight-hd-pack",
		"summary": "It's time to bask in the glory of beautiful 4k textures!",
		"description": "<p>Rogue HD Pack does exactly what you thi...",
		"description_plaintext": "Rogue HD Pack does exactly what you thi...",
		"metadata_blob": "rogue,hd,high-res,4k,hd textures",
		"profile_url": "https://rogue-knight.mod.io/rogue-knight-hd-pack",
		"media": {
			"youtube": [
				"https://www.youtube.com/watch?v=dQw4w9WgXcQ"
			],
			"sketchfab": [
				"https://sketchfab.com/models/ef40b2d300334d009984c8865b2db1c8"
			],
			"images": [
				{
					"filename": "modio-color-dark.png",
					"original": "https://static.mod.io/v1/images/original.png",
					"thumb_320x180": "https://static.mod.io/v1/images/thumb_320x180.png"
				}
			]
		},
		"modfile": {
			"id": 2,
			"mod_id": 2,
			"date_added": 1499841487,
			"date_scanned": 1499841487,
			"virus_status": 0,
			"virus_positive": 0,
			"virustotal_hash": "f9a7bf4a95ce20787337b685a79677cae2281b83c63ab0a25f091407741692af-1508147401",
			"filesize": 15181,
			"filehash": {
				"md5": "2d4a0e2d7273db6b0a94b0740a88ad0d"
			},
			"filename": "rogue-knight-v1.zip",
			"version": "1.3",
			"changelog": "VERSION 1.3 -- Changes -- Fixed critical castle floor bug.",
			"metadata_blob": "rogue,hd,high-res,4k,hd textures",
			"download": {
				"binary_url": "https://mod.io/mods/file/1/c489a0354111a4d76640d47f0cdcb294",
				"date_expires": 1579316848
			}
		},
		"metadata_kvp": [
			{
				"metakey": "pistol-dmg",
				"metavalue": "800"
			}
		],
		"tags": [
			{
				"name": "Unity",
				"date_added": 1499841487
			}
		],
		"stats": {
			"mod_id": 2,
			"popularity_rank_position": 13,
			"popularity_rank_total_mods": 204,
			"downloads_total": 27492,
			"subscribers_total": 16394,
			"ratings_total": 1230,
			"ratings_positive": 1047,
			"ratings_negative": 183,
			"ratings_percentage_positive": 91,
			"ratings_weighted_aggregate": 87.38,
			"ratings_display_text": "Very Positive",
			"date_expires": 1492564103
		}
	}
)"_json;