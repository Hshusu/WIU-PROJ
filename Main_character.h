#pragma once
#include "Player.h"
#include"Item.h"
#include"inventory.h"
#include"AttackGame.h"
class Main_character : public Player
{
private:
	// | 0 is STR | 1 is DEX | 2 is INT | 3 is VIT | 4 is LUK | 5 is WIS | 
	float character_Base_Stats[6] = { 15, 15, 15, 15, 15, 15 };
	int character_Level[6] = { 0, 0, 0, 0, 0, 0 };
	inventory player_inv = inventory(10,5);
	static const int maxitm = 100;
	Item* Itemptr[maxitm] = { NULL };
	int dmg;
	bool InventoryActive = false;
	int HealthPotCount = 0;
	int MaxHealthPot = 5;

	int ManaPotCount = 6;
	int MaxManaPotCount = 10;

	int StatPotCount = 11;
	int MaxStatPotCount = 15;

	static int playerLevel;
	static int playerExp;
	static int playerCoins;

public:
	float character_Modifiers[6] = { 0, 0, 0, 0, 0, 0 };

	static int getPlayerLevel(void);
	static int getPlayerExp(void);
	static int getPlayerCoins(void);

	static void setPlayerLevel(int pL);
	static void setPlayerExp(int pE, int& States);
	static void setPlayerCoins(int pC);

	void statpotion();
	void StatPotCounter();
	int GetStatPotCount(void);

	void HealthPotCounter();
	int GetHealthPotCount(void);
	void Consumable(int itemid);
	void ManaPotCounter();
	int GetManaPotCount(void);
	Main_character(float character_Modifiers[6], std::string Name, int Weak, int Res);
	void inv(int x, int y, std::string name, int ID);
	int inv();
	void CalculateStats();
	void ExecuteSkill(Entity* Enemy, int Choice);
};

