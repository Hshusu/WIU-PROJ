#include "Clue.h"

std::string Clue::getName(void) const
{
	return Name;
}

std::string Clue::getDescription(void) const
{
	return Description;
}

ClueType Clue::getType(void) const
{
	return Type;
}

Clue::Clue(const std::string& Name, const std::string& Description, ClueType Type)
{
	this->Name = Name;
	this->Description = Description;
	this->Type = Type;
}