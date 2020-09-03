#include <iostream>
#include "gtest/gtest.h"
#include "c/ModioC.h"
#include "c/schemas/ModioLogo.h"
#include "c/schemas/ModioIcon.h"
#include "c/schemas/ModioHeader.h"
#include "c/schemas/ModioAvatar.h"
#include "c/schemas/ModioImage.h"
#include "c/schemas/ModioDependency.h"
#include "c/schemas/ModioComment.h"
#include "c/schemas/ModioGameTagOption.h"
#include "c/schemas/ModioModfile.h"
#include "c/schemas/ModioFilehash.h"
#include "c/schemas/ModioDownload.h"
#include "c/schemas/ModioGame.h"
#include "c/schemas/ModioMedia.h"
#include "c/schemas/ModioTag.h"
#include "c/schemas/ModioMetadataKVP.h"
#include "c/schemas/ModioRating.h"
#include "c/schemas/ModioStats.h"
#include "c/schemas/ModioUser.h"
#include "json_examples.h"

TEST(SchemaIntialization, TestModioLogoInitialization)
{
	ModioLogo logo;
	modioInitLogo(&logo, logo_json);

	EXPECT_STREQ(logo.filename, "modio-color-dark.png");
	EXPECT_STREQ(logo.original, "https://static.mod.io/v1/images/branding/modio-color-dark.png");
	EXPECT_STREQ(logo.thumb_320x180, "https://static.mod.io/v1/images/thumb_320x180.png");
	EXPECT_STREQ(logo.thumb_640x360, "https://static.mod.io/v1/images/thumb_640x360.png");
	EXPECT_STREQ(logo.thumb_1280x720, "https://static.mod.io/v1/images/thumb_1280x720.png");

	modioFreeLogo(&logo);
}

TEST(SchemaIntialization, TestModioIconInitialization)
{
	ModioIcon icon;
	modioInitIcon(&icon, icon_json);

	EXPECT_STREQ(icon.filename, "modio-color-dark.png");
	EXPECT_STREQ(icon.original, "https://static.mod.io/v1/images/original.png");
	EXPECT_STREQ(icon.thumb_64x64, "https://static.mod.io/v1/images/thumb_64x64.png");
	EXPECT_STREQ(icon.thumb_128x128, "https://static.mod.io/v1/images/thumb_128x128.png");
	EXPECT_STREQ(icon.thumb_256x256, "https://static.mod.io/v1/images/thumb_256x256.png");

	modioFreeIcon(&icon);
}

TEST(SchemaIntialization, TestModioHeaderImageInitialization)
{
	ModioHeader header;
	modioInitHeader(&header, header_image_json);

	EXPECT_STREQ(header.filename, "demo.png");
	EXPECT_STREQ(header.original, "https://static.mod.io/v1/images/original.png");

	modioFreeHeader(&header);
}

TEST(SchemaIntialization, TestModioAvatarInitialization)
{
	ModioAvatar avatar;
	modioInitAvatar(&avatar, avatar_json);

	EXPECT_STREQ(avatar.filename, "modio-color-dark.png");
	EXPECT_STREQ(avatar.original, "https://static.mod.io/v1/images/original.png");
	EXPECT_STREQ(avatar.thumb_50x50, "https://static.mod.io/v1/images/thumb_50x50.png");
	EXPECT_STREQ(avatar.thumb_100x100, "https://static.mod.io/v1/images/thumb_100x100.png");

	modioFreeAvatar(&avatar);
}

TEST(SchemaIntialization, TestModioImageInitialization)
{
	ModioImage image;
	modioInitImage(&image, image_json);

	EXPECT_STREQ(image.filename, "modio-color-dark.png");
	EXPECT_STREQ(image.original, "https://static.mod.io/v1/images/original.png");
	EXPECT_STREQ(image.thumb_320x180, "https://static.mod.io/v1/images/thumb_320x180.png");

	modioFreeImage(&image);
}

TEST(SchemaIntialization, TestModioModEventInitialization)
{
	ModioModEvent event;
	modioInitModEvent(&event, event_json);

	EXPECT_EQ(event.id, 13);
	EXPECT_EQ(event.mod_id, 14);
	EXPECT_EQ(event.user_id, 15);
	EXPECT_EQ(event.date_added, 1499846132);
	EXPECT_EQ(event.event_type, MODIO_EVENT_MODFILE_CHANGED);

	modioFreeModEvent(&event);
}

TEST(SchemaIntialization, TestModioCommentInitialization)
{
	ModioComment comment;
	modioInitComment(&comment, comment_json);

	EXPECT_EQ(comment.id, 2);
	EXPECT_EQ(comment.mod_id, 3);
	EXPECT_EQ(comment.date_added, 1499841487);
	EXPECT_EQ(comment.reply_id, 1499);
	EXPECT_STREQ(comment.thread_position, "01");
	EXPECT_EQ(comment.karma, 1);
	EXPECT_EQ(comment.karma_guest, 0);
	EXPECT_STREQ(comment.content, "This mod is kickass! Great work!");

	modioFreeComment(&comment);
}

TEST(SchemaIntialization, TestModioDependencyInitialization)
{
	ModioDependency dependency;
	modioInitDependency(&dependency, mod_dependency_json);

	EXPECT_EQ(dependency.mod_id, 231);
	EXPECT_EQ(dependency.date_added, 1499841487);

	modioFreeDependency(&dependency);
}

TEST(SchemaIntialization, TestModioGameTagOptionInitialization)
{
	ModioGameTagOption game_tag_option;
	modioInitGameTagOption(&game_tag_option, game_tag_option_json);

	EXPECT_STREQ(game_tag_option.name, "Theme");
	EXPECT_STREQ(game_tag_option.type, "checkboxes");
	EXPECT_EQ(game_tag_option.tags_array_size, 1);
	EXPECT_STREQ(game_tag_option.tags_array[0], "Horror");
	EXPECT_EQ(game_tag_option.hidden, false);

	modioFreeGameTagOption(&game_tag_option);
}

TEST(SchemaIntialization, TestModioModfileInitialization)
{
	ModioModfile modfile;
	modioInitModfile(&modfile, modfile_json);

	EXPECT_EQ(modfile.id, 2);
	EXPECT_EQ(modfile.mod_id, 3);
	EXPECT_EQ(modfile.date_added, 1499841487);
	EXPECT_EQ(modfile.date_scanned, 1499841487);
	EXPECT_EQ(modfile.virus_status, 5);
	EXPECT_EQ(modfile.virus_positive, 1);
	EXPECT_STREQ(modfile.virustotal_hash, "f9a7bf4a95ce20787337b685a79677cae2281b83c63ab0a25f091407741692af-1508147401");
	EXPECT_EQ(modfile.filesize, 15181);
	EXPECT_STREQ(modfile.filename, "rogue-knight-v1.zip");
	EXPECT_STREQ(modfile.version, "1.3");
	EXPECT_STREQ(modfile.changelog, "VERSION 1.3 -- Changes -- Fixed critical castle floor bug.");
	EXPECT_STREQ(modfile.metadata_blob, "rogue,hd,high-res,4k,hd textures");

	modioFreeModfile(&modfile);
}

TEST(SchemaIntialization, TestModioFilehashInitialization)
{
	ModioFilehash filehash;
	modioInitFilehash(&filehash, filehash_json);

	EXPECT_STREQ(filehash.md5, "2d4a0e2d7273db6b0a94b0740a88ad0d");

	modioFreeFilehash(&filehash);
}

TEST(SchemaIntialization, TestModioDownloadInitialization)
{
	ModioDownload download;
	modioInitDownload(&download, download_json);

	EXPECT_STREQ(download.binary_url, "https://mod.io/mods/file/1/c489a0354111a4d76640d47f0cdcb294");
	EXPECT_EQ(download.date_expires, 1579316848);

	modioFreeDownload(&download);
}

TEST(SchemaIntialization, TestModioGameInitialization)
{
	ModioGame game;
	modioInitGame(&game, game_json);

	EXPECT_EQ(game.id, 2);
	EXPECT_EQ(game.status, 1);
	EXPECT_EQ(game.date_added, 1493702614);
	EXPECT_EQ(game.date_updated, 1499410290);
	EXPECT_EQ(game.date_live, 1499841403);
	EXPECT_EQ(game.presentation_option, 1);
	EXPECT_EQ(game.submission_option, 0);
	EXPECT_EQ(game.curation_option, 0);
	EXPECT_EQ(game.community_options, 3);
	EXPECT_EQ(game.revenue_options, 1500);
	EXPECT_EQ(game.api_access_options, 3);
	EXPECT_EQ(game.maturity_options, 0);
	EXPECT_STREQ(game.ugc_name, "map");
	EXPECT_STREQ(game.name, "Rogue Knight");
	EXPECT_STREQ(game.name_id, "rogue-knight");
	EXPECT_STREQ(game.summary, "Rogue Knight is a brand new 2D pixel platformer.");
	EXPECT_STREQ(game.instructions, "Instructions on the process to upload mods.");
	EXPECT_STREQ(game.instructions_url, "https://www.rogue-knight-game.com/modding/getting-started");
	EXPECT_STREQ(game.profile_url, "https://rogue-knight.mod.io");

	modioFreeGame(&game);
}

TEST(SchemaIntialization, TestModioMediaInitialization)
{
	ModioMedia media;
	modioInitMedia(&media, mod_media_json);

	EXPECT_EQ(media.youtube_size, 1);
	EXPECT_STREQ(media.youtube_array[0], "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
	EXPECT_EQ(media.sketchfab_size, 1);
	EXPECT_STREQ(media.sketchfab_array[0], "https://sketchfab.com/models/ef40b2d300334d009984c8865b2db1c8");
	EXPECT_EQ(media.images_size, 1);
	EXPECT_STREQ(media.images_array[0].filename, "modio-color-dark.png");
	EXPECT_STREQ(media.images_array[0].original, "https://static.mod.io/v1/images/original.png");
	EXPECT_STREQ(media.images_array[0].thumb_320x180, "https://static.mod.io/v1/images/thumb_320x180.png");

	modioFreeMedia(&media);
}

TEST(SchemaIntialization, TestModioTagInitialization)
{
	ModioTag tag;
	modioInitTag(&tag, mod_tag_json);

	EXPECT_STREQ(tag.name, "Unity");
	EXPECT_EQ(tag.date_added, 1499841487);

	modioFreeTag(&tag);
}

TEST(SchemaIntialization, TestModioModInitialization)
{
	ModioMod mod;
	modioInitMod(&mod, mod_json);

	EXPECT_EQ(mod.id, 2);
	EXPECT_EQ(mod.game_id, 2);
	EXPECT_EQ(mod.status, 1);
	EXPECT_EQ(mod.visible, 1);
	EXPECT_EQ(mod.date_added, 1492564103);
	EXPECT_EQ(mod.date_updated, 1499841487);
	EXPECT_EQ(mod.date_live, 1499841403);
	EXPECT_EQ(mod.maturity_option, 0);
	EXPECT_STREQ(mod.homepage_url, "https://www.rogue-hdpack.com/");
	EXPECT_STREQ(mod.name, "Rogue Knight HD Pack");
	EXPECT_STREQ(mod.name_id, "rogue-knight-hd-pack");
	EXPECT_STREQ(mod.summary, "It's time to bask in the glory of beautiful 4k textures!");
	EXPECT_STREQ(mod.description, "<p>Rogue HD Pack does exactly what you thi...");
	EXPECT_STREQ(mod.description_plaintext, "Rogue HD Pack does exactly what you thi...");
	EXPECT_STREQ(mod.metadata_blob, "rogue,hd,high-res,4k,hd textures");
	EXPECT_STREQ(mod.profile_url, "https://rogue-knight.mod.io/rogue-knight-hd-pack");

	modioFreeMod(&mod);
}

TEST(SchemaIntialization, TestModioMetadataKVPInitialization)
{
	ModioMetadataKVP metadata_kvp;
	modioInitMetadataKVP(&metadata_kvp, metadata_kvp_json);

	EXPECT_STREQ(metadata_kvp.metakey, "pistol-dmg");
	EXPECT_STREQ(metadata_kvp.metavalue, "800");

	modioFreeMetadataKVP(&metadata_kvp);
}

TEST(SchemaIntialization, TestModioRatingInitialization)
{
	ModioRating rating;
	modioInitRating(&rating, rating_json);

	EXPECT_EQ(rating.game_id, 2);
	EXPECT_EQ(rating.mod_id, 3);
	EXPECT_EQ(rating.rating, -1);
	EXPECT_EQ(rating.date_added, 1492564103);

	modioFreeRating(&rating);
}

TEST(SchemaIntialization, TestModioStatsInitialization)
{
	ModioStats stats;
	modioInitStats(&stats, stats_json);

	EXPECT_EQ(stats.mod_id, 2);
	EXPECT_EQ(stats.popularity_rank_position, 13);
	EXPECT_EQ(stats.popularity_rank_total_mods, 204);
	EXPECT_EQ(stats.downloads_total, 27492);
	EXPECT_EQ(stats.subscribers_total, 16394);
	EXPECT_EQ(stats.ratings_total, 1230);
	EXPECT_EQ(stats.ratings_positive, 1047);
	EXPECT_EQ(stats.ratings_negative, 183);
	EXPECT_EQ(stats.ratings_percentage_positive, 91);
	EXPECT_EQ(stats.ratings_weighted_aggregate, 87.38);
	EXPECT_STREQ(stats.ratings_display_text, "Very Positive");
	EXPECT_EQ(stats.date_expires, 1492564103);

	modioFreeStats(&stats);
}

TEST(SchemaIntialization, TestModioUserInitialization)
{
	ModioUser user;
	modioInitUser(&user, user_json);

	EXPECT_EQ(user.id, 1);
	EXPECT_STREQ(user.name_id, "xant");
	EXPECT_STREQ(user.username, "XanT");
	EXPECT_EQ(user.date_online, 1509922961);
	EXPECT_STREQ(user.timezone, "America/Los_Angeles");
	EXPECT_STREQ(user.language, "en");
	EXPECT_STREQ(user.profile_url, "https://mod.io/members/xant");

	modioFreeUser(&user);
}