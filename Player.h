#pragma once
#include "Entity.h"

#include <iostream>
#include <conio.h>
#include <windows.h>

class Player : public Entity
{
private:

	int scrollPos = 0;
public:
	int getSkillCount();
	int PlayerTurn(Entity* Enemy);
	void GenerateUI(Entity Enemy);
	void DisplaySkills(int i);
	virtual void displaystats();
	Player(std::string Name, float DMGModifier, float MaxHp, float Speed, float MaxMana, int Weak, int Res);
	Player();
};

