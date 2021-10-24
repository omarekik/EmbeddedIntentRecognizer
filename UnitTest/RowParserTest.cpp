#include <gtest/gtest.h>
#include "RowParser.h"

TEST(RowParser, canParseSentence){
    const std::string sentence = "What is the weather like today?";
    RowParser row_parser(sentence);
    std::string result = "";
    for(boost::tokenizer<>::iterator it=row_parser.getWords().begin(); it!=row_parser.getWords().end();++it){
       result += *it ;
    }
    EXPECT_STREQ("Whatistheweatherliketoday", result.c_str());  
}

