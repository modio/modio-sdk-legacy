#include "json_examples.h"

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
      "original": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
      "thumb_50x50": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
      "thumb_100x100": "https://static.mod.io/v1/images/branding/modio-color-dark.png"
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
    "original": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
    "thumb_64x64": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
    "thumb_128x128": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
    "thumb_256x256": "https://static.mod.io/v1/images/branding/modio-color-dark.png"
  },
  "logo": {
    "filename": "modio-color-dark.png",
    "original": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
    "thumb_320x180": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
    "thumb_640x360": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
    "thumb_1280x720": "https://static.mod.io/v1/images/branding/modio-color-dark.png"
  },
  "header": {
    "filename": "demo.png",
    "original": "https://static.mod.io/v1/images/branding/modio-color-dark.png"
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
				"original": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
				"thumb_50x50": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
				"thumb_100x100": "https://static.mod.io/v1/images/branding/modio-color-dark.png"
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
			"original": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
			"thumb_320x180": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
			"thumb_640x360": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
			"thumb_1280x720": "https://static.mod.io/v1/images/branding/modio-color-dark.png"
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
					"original": "https://static.mod.io/v1/images/branding/modio-color-dark.png",
					"thumb_320x180": "https://static.mod.io/v1/images/branding/modio-color-dark.png"
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