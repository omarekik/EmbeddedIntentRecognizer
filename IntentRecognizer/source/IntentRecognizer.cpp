#include "IntentRecognizer.h"
#include <algorithm>
#include <execution>
#include <boost/algorithm/string.hpp>


void IntentRecognizer::emplaceIntent(Intent intent)
{
    m_Intents.emplace_back(std::move(intent));
}

void IntentRecognizer::recognize(std::string sentence)
{
    boost::to_upper(sentence);
    for_each( std::execution::par_unseq
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
    for_each( std::begin(m_Intents)
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