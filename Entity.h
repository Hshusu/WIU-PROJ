#pragma once
#include"Equipment.h"

#include <iostream>
#include <vector>
#include <string>
#include "Dodge.h"
enum element {
	Fire,
	Ice,
	Lightning,
	Wind,
	Darkness,
	Siphon,
	None,
	Healing
};

struct SkillDetails {
	std::string Name;
	std::string Description;
	int Cost;
	int Base;
	bool ManaCost;
	bool Healing;
	bool Blocking;
	bool Inventory = false;
	int Element = None;
	int CR_Manipulation = 0;
};

class Entity
{
protected:
	int Weakness = None;
	int Resistance = None;
	Equipment* Weapon;
	Equipment* Armor;
	std::string Name;
	float DMGModifier;
	float MagicModifier;
	float Mana;
	float speed;
	float CombatReady =0;
	float HP;
	float MaxMana;
	float MaxHp;
	bool Blocking = false;
	bool Turn = false;
	std::vector<SkillDetails>Skills;
public:
	std::string getName();
	float getSpeed();
	float getHP();
	float getMaxHP();
	void resethp();
	float getCR();
	float getMana();
	int getWeakness();
	int getResistance();
	bool getBlocking();
	int getWeaponVal();
	int getArmorVal();
	
	bool CheckCR();
	void UpdateCR(int newCR);

	bool getTurn();
	void setTurn(bool Go);

	void TakeDMG(int Damage);
	virtual void ExecuteSkill(Entity* Enemy, int Choice);
};
