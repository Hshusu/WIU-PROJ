#pragma once
#include "Entity.h"

#include <iostream>
#include <conio.h>
#include <windows.h>

class Player : public Entity
{
private:
	// | 0 is STR | 1 is DEX | 2 is INT | 3 is VIT | 4 is LUK | 5 is WIS | 
	float character_Base_Stats[6] = { 10, 10, 10, 10, 10, 10 };
	float character_Modifiers[6] = { 0, 0, 0, 0, 0, 0 };
	int character_Level[6] = { 0, 0, 0, 0, 0, 0 };
	int scrollPos = 0;
public:
	int getSkillCount();
	int PlayerTurn(Entity* Enemy);

	void GenerateUI(Entity Enemy);
	void CalculateStats();
	void DisplaySkills(int i);

	Player(std::string Name, float DMGModifier, float MaxHp, float Speed, float MaxMana, int Weak, int Res);
	Player(float character_Modifiers[6], std::string Name, int Weak, int Res);
};

