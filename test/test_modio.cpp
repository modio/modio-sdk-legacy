#include <iostream>
#include "gtest/gtest.h"
#include "modio.h"
#include "json_examples.h"

//modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

TEST(IndependentMethod, TestModioGameInitialization)
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

TEST(IndependentMethod, TestModioModInitialization)
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