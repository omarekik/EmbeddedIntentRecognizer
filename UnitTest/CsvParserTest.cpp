#include <gtest/gtest.h>
#include "CsvParser.h"


TEST(CsvParser, canParseCsv){
    CsvParser csv_parser ("intention.csv");
    std::string intents = "";
    for(auto & row : csv_parser.getData())
    {
        intents += row.first + "|";
    }  
    EXPECT_STREQ("GET|BRAND|CLOTHES|WEEK|FOOTWEAR|MONTH|GREETING|TRANSPORT|FAMILY|WEATHER|CITY|FACT|"
                , intents.c_str());
}
