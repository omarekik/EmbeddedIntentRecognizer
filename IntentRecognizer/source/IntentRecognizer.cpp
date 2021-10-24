#include "IntentRecognizer.h"
#include <algorithm>
#include <execution>

bool Intent::find(const std::string & word)
{
    m_Found = m_Context.find(word)!=m_Context.end();
    return m_Found;
}

void IntentRecognizer::emplaceIntent(Intent intent)
{
    m_Intents.emplace_back(std::move(intent));
}

void IntentRecognizer::recognize(const std::string & word)
{
    for_each( std::execution::par
                            , std::begin(m_Intents)
                            , std::end(m_Intents)
                            , [& word](Intent & intent){
                                if(!intent.getFound()){
                                    intent.find(word);
                                }
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