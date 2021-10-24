#include <gtest/gtest.h>
#include "IntentRecognizer.h"
#include <set>
#include <list>
#include <algorithm>
#include <execution>

TEST(Intent, canFindWord)
{
    Intent intent({"hello", "Hi", "morning"}, "GREETING");
    EXPECT_FALSE(intent.find("coffee"));
    EXPECT_TRUE(intent.find("Hi"));
}

TEST(IntentRecognizer, canRecognizeIntentes){
    const std::set<std::string> input = {"hello", "my", "son"};
    IntentRecognizer intent_recognizer;
    intent_recognizer.emplaceIntent(Intent({"hello", "Hi", "morning"}, "GREETING"));
    intent_recognizer.emplaceIntent(Intent({"father", "mother", "son"}, "FAMILY"));
    intent_recognizer.emplaceIntent(Intent({"car", "bus", "airplan"}, "TRANSPORTATION"));
    for_each( std::execution::par
            , std::begin(input)
            , std::end(input)
            , [& intent_recognizer](const std::string & input_element)
                {
                    intent_recognizer.recognize(input_element);
                }
        );
    EXPECT_STREQ("Intent: GREETING FAMILY", intent_recognizer.getRecognizedIntents().c_str());
}

