#include<boost/tokenizer.hpp>
class RowParser
{
private:
    boost::tokenizer<> words;
public:
    RowParser(const std::string & row);
    const boost::tokenizer<> getWords() const {return words;}
};