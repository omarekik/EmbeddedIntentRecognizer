#include <gtest/gtest.h>
#include "Intent.h"

TEST(Intent, canFindContextInSentence)
{
    Intent intent({"HELLO", "HI", "MORNING"}, "GREETING");
    EXPECT_FALSE(intent.find("IT WILL BE THE BEST DAY."));
    EXPECT_TRUE(intent.find("GOOD MORNING MY CAR."));
}

TEST(Intent, canFindExpressionContextInSentence)
{
    Intent intent({"HELLO", "HI", "MORNING"}, "GREETING");
    EXPECT_FALSE(intent.find("IT WILL BE THE BEST DAY."));
    EXPECT_TRUE(intent.find("GOOD MORNING MY CAR."));
}

TEST(Intent, canFindContextInSentenceCaseInsensitive)
{
    Intent intent({"HELLO", "HI", "MORNING"}, "GREETING");
    EXPECT_TRUE(intent.find("HELLO MY CAR."));
}