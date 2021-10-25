#pragma once

#include <vector>
#include <string>

class Intent{
    const std::vector<std::string> m_Context;
    const std::string m_Name;
    bool m_Found;
public:
    Intent(const std::vector<std::string> context, const std::string name)
        : m_Context(context)
        , m_Name(name)
        , m_Found(false)
        {}
    Intent(const Intent & intent) = delete;
    Intent & operator=(const Intent & intent) = delete;
    Intent(Intent && intent) = default;

    bool find(const std::string & sentence);
    const bool getFound() const {return m_Found;}
    const std::string & getName() const {return m_Name;}
    const std::string serialize() const;
};