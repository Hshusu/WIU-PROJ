#pragma once
#include "Player.h"
#include"Item.h"
#include"inventory.h"
#include"AttackGame.h"
class Main_character : public Player
{
private:
	// | 0 is STR | 1 is DEX | 2 is INT | 3 is VIT | 4 is LUK | 5 is WIS | 
	float character_Base_Stats[6] = { 10, 10, 10, 10, 10, 10 };
	float character_Modifiers[6] = { 0, 0, 0, 0, 0, 0 };
	int character_Level[6] = { 0, 0, 0, 0, 0, 0 };
	inventory player_inv = inventory(10,5);
	Item* Itemptr[20] = { NULL };
	int dmg;
public:
	Main_character(float character_Modifiers[6], std::string Name, int Weak, int Res);
	void inv(int x, int y, std::string name, int ID);
	int inv();
	void CalculateStats();
	void ExecuteSkill(Entity* Enemy, int Choice);
};

