#include "IntentRecognizer.h"
#include <algorithm>
#include <execution>
#include <boost/algorithm/string/find.hpp>

bool Intent::find(const std::string & sentence)
{
    typedef const boost::iterator_range<std::string::const_iterator> StringRange;
    m_Found = std::find_if( std::execution::par
                          , std::begin(m_Context)
                          , std::end(m_Context)
                          , [&sentence](const std::string & context_element) {
                              return boost::ifind_first( StringRange(std::begin(sentence), std::end(sentence))
                                                       , StringRange(std::begin(context_element), std::end(context_element)));
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

void IntentRecognizer::emplaceIntent(Intent intent)
{
    m_Intents.emplace_back(std::move(intent));
}

void IntentRecognizer::recognize(const std::string & sentence)
{

    for_each( std::execution::par
            , std::begin(m_Intents)
            , std::end(m_Intents)
            , [& sentence](Intent & intent){
                    intent.find(sentence);
            }
        );
}

const std::string IntentRecognizer::getRecognizedIntents() const 
{
    std::string res = "Intent:";
    for_each( std::execution::seq
            , std::begin(m_Intents)
            , std::end(m_Intents)
            , [& res](const Intent & intent){
                if(intent.getFound()){
                    res += " " + intent.getName();
                }
            }
        );
    return res;
}

const std::string IntentRecognizer::serialize() const
{
    std::string res = "";
    for(auto & intent : m_Intents)
    {
        res += intent.serialize();
        res += "\n";
    }
    return res;
}