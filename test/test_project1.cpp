#include <iostream>
#include "gtest/gtest.h"
#include "modio.h"
#include "examples.h"


// IndependentMethod is a test case - here, we have 2 tests for this 1 test case
TEST(IndependentMethod, ResetsToZero) {
	modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

	ModioMod mod;

	
	modioInitMod(&mod, mod_json);

	EXPECT_EQ(mod.id,2);
	EXPECT_EQ(mod.game_id,2);
	EXPECT_EQ(mod.status,1);
}