#pragma once

#include <string>
#include <unordered_set>
#include <list>
#include <atomic>

class Intent{
    const std::unordered_set<std::string> m_Context;
    const std::string m_Name;
    std::atomic_bool m_Found;
public:
    Intent(const std::unordered_set<std::string> context, const std::string name)
        : m_Context(context)
        , m_Name(name)
        , m_Found(false)
        {}
    Intent(const Intent & intent) = delete;
    Intent & operator=(const Intent & intent) = delete;
    Intent(Intent && intent) : m_Context(std::move(intent.m_Context))
                    , m_Name(std::move(intent.m_Name))
                    , m_Found(static_cast< bool >(intent.m_Found))
                    {}

    bool find(const std::string & word);
    const bool getFound() const {return m_Found;}
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
