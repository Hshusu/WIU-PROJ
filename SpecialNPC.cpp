#include "SpecialNPC.h"

std::string SpecialNPC::getNPCName(void) const
{
	return NPCName;
}

std::string SpecialNPC::getNPCTestimony(void) const
{
	return NPCTestimony;
}

SpecialNPC::SpecialNPC(const std::string& Name, const std::string& Testimony)
{
	NPCName = Name;
	NPCTestimony = Testimony;
}