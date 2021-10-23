#include "RowParser.h"

RowParser::RowParser(const std::string & row) : words(boost::tokenizer<>(row)) 
{
    
}
