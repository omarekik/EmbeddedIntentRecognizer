#include <gtest/gtest.h>
#include "IntentRecognizer.h"
#include "CsvParser.h"

TEST(IntentRecognizer, canRecognizeIntentes){
    const std::string input = "hello my Son.";
    IntentRecognizer intent_recognizer;
    intent_recognizer.emplaceIntent(Intent({"HELLO", "HI", "MORNING"}, "GREETING"));
    intent_recognizer.emplaceIntent(Intent({"FATHER", "MOTHER", "SON"}, "FAMILY"));
    intent_recognizer.emplaceIntent(Intent({"CAR", "BUS", "AIRPLAN"}, "TRANSPORTATION"));

    intent_recognizer.recognize(input);
    EXPECT_STREQ("Intent: GREETING FAMILY", intent_recognizer.getRecognizedIntents().c_str());
}

TEST(IntentRecognizer, canRecognizeCsvIntentes){
    const std::string input = "Hello my son.";
    IntentRecognizer intent_recognizer;

    CsvParser csv_parser ("intention.csv");
    for(auto & row : csv_parser.getData())
    {
        intent_recognizer.emplaceIntent(Intent(std::move(row.second), std::move(row.first)));
    }  

    //std::cout<< intent_recognizer.serialize() << "\n";
    intent_recognizer.recognize(input);
    std::string recognized_intents = intent_recognizer.getRecognizedIntents();
    //std::cout<< recognized_intents << "\n";
    EXPECT_STREQ("Intent: GREETING FAMILY", recognized_intents.c_str());
}



