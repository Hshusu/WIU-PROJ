#pragma once
#include "Entity.h"
#include "Utility.h"
class NPC :public Entity
{
public:
	int ChooseAction();

	NPC(std::string Name, float DMGModifier, float MaxHp, float Speed, float MaxMana, int Weak, int Res);
};

