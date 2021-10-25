#pragma once

#include <vector>
#include <list>
#include <utility>
#include <string>

class CsvParser{
    using DataType = std::list<std::pair<std::string, std::vector<std::string>>>;
    DataType m_Data;
public:
    CsvParser(const std::string & filename);
    DataType & getData() {return m_Data;}
};