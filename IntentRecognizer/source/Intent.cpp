#include "Intent.h"
#include <execution>

bool Intent::find(const std::string & sentence)
{
    m_Found = std::find_if( std::execution::par_unseq
                          , std::begin(m_Context)
                          , std::end(m_Context)
                          , [&sentence](const std::string & context_element) {
                                return sentence.find(context_element) != std::string::npos;
                            }
                          ) != std::end(m_Context);
    return m_Found;
}

const std::string Intent::serialize() const
{
    std::string res = "";
    res += m_Found;
    res += '|';
    res += m_Name;
    res += '|';
    for(auto & context_element : m_Context)
    {
        res += context_element;
        res += '|';
    }
    return res;
}