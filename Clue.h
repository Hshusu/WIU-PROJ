#pragma once
#include <string>

enum class ClueType { Physical, Testimonial, Analytical, Herring };

class Clue {
private:
    std::string Name;
    std::string Description;
    ClueType Type;
public:
    std::string getName(void) const;
    std::string getDescription(void) const;
    ClueType getType(void) const;

    Clue(const std::string& Name, const std::string& Description, ClueType Type);
};