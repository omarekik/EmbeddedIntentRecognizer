#include "CsvParser.h"
#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

CsvParser::CsvParser(const std::string & filename)
{
    std::ifstream csv_file(filename);
    std::string line;
    while (std::getline(csv_file, line))
    {
        std::vector<std::string> context;
        boost::split(context, line, boost::is_any_of(","));
        if(!context.empty())
        {
            std::string name = context[0];
            context.erase(context.begin());
            m_Data.emplace_back(std::make_pair(std::move(name), std::move(context)));
        }
    }
    csv_file.close();
}