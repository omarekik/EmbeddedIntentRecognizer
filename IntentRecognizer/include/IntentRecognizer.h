#pragma once

#include <list>
#include "Intent.h"

class IntentRecognizer
{
private:
    std::list<Intent> m_Intents;
    
public:
    void emplaceIntent(Intent intent);
    void recognize(std::string sentence);
    const std::string getRecognizedIntents() const;
    const std::string serialize()const;
};
