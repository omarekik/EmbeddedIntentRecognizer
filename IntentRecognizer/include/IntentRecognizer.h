#pragma once

#include <string>
#include <unordered_set>
#include <list>

class Intent{
    const std::unordered_set<std::string> m_Context;
    const std::string m_Name;
    bool m_Found;
public:
    Intent(const std::unordered_set<std::string> context, const std::string name)
        : m_Context(context)
        , m_Name(name)
        , m_Found(false)
        {}
    Intent(const Intent & intent) = delete;
    Intent(Intent && intent) = default;
    Intent & operator=(const Intent & intent) = delete;

    bool find(const std::string & word);
    const bool & getFound() const {return m_Found;}
    const std::string & getName() const {return m_Name;}
};

class IntentRecognizer
{
private:
    std::list<Intent> m_Intents;
    
public:
    void emplaceIntent(Intent intent);
    void recognize(const std::string & word);
    const std::string getRecognizedIntents() const;
};
