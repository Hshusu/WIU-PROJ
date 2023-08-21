#pragma once
#include "Entity.h"
class Npc:public Entity
{
public:
	Npc(std::string name, float dmgmod, float MaxHp, float speed, float MaxMana, int Weak, int res);
	int chooseaction();
	void Execute_skill(Entity* Enemy, int choice);
};

