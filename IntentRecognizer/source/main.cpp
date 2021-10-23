#include<iostream>
#include "RowParser.h"

int main(int argc, char* argv[])
{
   const std::string sentence = "What is the weather like today?";
   RowParser row_parser(sentence);
   for(boost::tokenizer<>::iterator it=row_parser.getWords().begin(); it!=row_parser.getWords().end();++it){
       std::cout << *it << "\n";
   }
}
