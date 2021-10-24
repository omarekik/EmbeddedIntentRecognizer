#include <gtest/gtest.h>
#include "IntentRecognizer.h"
#include <csv.hpp>


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

TEST(IntentRecognizer, canRecognizeCsvIntentes){
    const std::string input = "Hello my son.";
    IntentRecognizer intent_recognizer;

    csv::CSVReader reader("intentionLight.csv");
    for (csv::CSVRow& row: reader) { 
        std::vector<std::string> context = row;
        std::string name = context[0];
        context.erase(context.begin());
        intent_recognizer.emplaceIntent(Intent(std::move(context), std::move(name)));
    }
    std::cout<< intent_recognizer.serialize() << "\n";
    intent_recognizer.recognize(input);
    std::string recognized_intents = intent_recognizer.getRecognizedIntents();
    std::cout<< recognized_intents << "\n";
    EXPECT_STREQ("Intent: GREETING FAMILY", recognized_intents.c_str());
}



