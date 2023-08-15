#pragma once
#include "Entity.h"
class Npc:public Entity
{
public:
	Npc(std::string name, float dmgmod, float MaxHp, float speed, float MaxMana);
	int chooseaction();
};

