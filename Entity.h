#pragma once
#include<vector>
#include<string>
#include"Equipment.h"
struct skilldetail {
	std::string name;
	std::string description; 
	int cost;
	int base;
	bool manacost;
	bool healing;
	bool blocking;

};
class Entity
{
protected:
	Equipment* weapon;
	Equipment* armor;
	std::string name;
	float dmgmod;
	float magicmod;
	float mana;
	float speed;
	float CR;
	float Hp;
	float MaxMana;
	float MaxHp;
	bool blocking=false;
	bool turn = false;
	std::vector<skilldetail>skills;
public:
	void takedmg(int x);
	std::string getname();
	float gethp();
	float getmana();
	int getweaponval();
	bool getturn();
	void setturn(bool x);
	int getarmorval();
	bool getblocking();
	float getspeed();
	bool CrCheck();
	void Execute_skill(Entity* Enemy, int choice);
	void damage(int x);



};
