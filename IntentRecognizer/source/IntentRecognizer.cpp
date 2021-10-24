#include "IntentRecognizer.h"
#include <algorithm>
#include <execution>

bool Intent::find(const std::string & sentence)
{
    for_each( std::execution::par
                , std::begin(m_Context)
                , std::end(m_Context)
                , [& m_Found = m_Found, & sentence](const std::string & context_element){
                    //
                    // May be after lauching thread per context_element one of them set m_Found to true
                    // so no need to run string::find in the remaining threads.
                    //
                    if(!m_Found){ 
                        if(sentence.find(context_element) != std::string::npos)
                        {
                            m_Found = true;
                        }
                    }
                }
            );
    return m_Found;
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