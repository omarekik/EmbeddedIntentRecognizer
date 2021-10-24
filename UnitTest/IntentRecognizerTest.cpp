#include <gtest/gtest.h>
#include "IntentRecognizer.h"
#include <set>
#include <list>
#include <algorithm>
#include <execution>

TEST(Intent, canFindContextInSentence)
{
    Intent intent({"hello", "Hi", "morning"}, "GREETING");
    EXPECT_FALSE(intent.find("It will be the best day."));
    EXPECT_TRUE(intent.find("Good morning my car."));
}

TEST(Intent, canFindExpressionContextInSentence)
{
    Intent intent({"hello", "Hi", "Good morning"}, "GREETING");
    EXPECT_FALSE(intent.find("It will be the best day."));
    EXPECT_TRUE(intent.find("Good morning my car."));
}

TEST(Intent, canFindContextInSentenceCaseInsensitive)
{
    Intent intent({"hello", "Hi", "Good morning"}, "GREETING");
    EXPECT_TRUE(intent.find("Hello my car."));
}

TEST(IntentRecognizer, canRecognizeIntentes){
    const std::string input = "hello my son.";
    IntentRecognizer intent_recognizer;
    intent_recognizer.emplaceIntent(Intent({"hello", "Hi", "morning"}, "GREETING"));
    intent_recognizer.emplaceIntent(Intent({"father", "mother", "son"}, "FAMILY"));
    intent_recognizer.emplaceIntent(Intent({"car", "bus", "airplan"}, "TRANSPORTATION"));
    intent_recognizer.recognize(input);

    EXPECT_STREQ("Intent: GREETING FAMILY", intent_recognizer.getRecognizedIntents().c_str());
}

