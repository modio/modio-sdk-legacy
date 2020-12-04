#include "Utility.h"
#include "gtest/gtest.h"

#define CH(HEX) std::string(1, (unsigned char)HEX)

TEST(Encoding, TestSingleLetters)
{
	EXPECT_EQ(modio::CP437ToUTF8(CH(0xf6)), "\xC3\xB7");
}