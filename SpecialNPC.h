#pragma once

#include <string>

class SpecialNPC
{
private:
    std::string NPCName;
    std::string NPCTestimony;
public:
    std::string getNPCName(void) const;
    std::string getNPCTestimony(void) const;

    SpecialNPC(const std::string& Name, const std::string& Testimony);
};