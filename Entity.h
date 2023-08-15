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
	float Hp;
	float MaxMana;
	float MaxHp;
	bool blocking=false;
	std::vector<skilldetail>skills;
public:
	Entity();
	Entity(std::string name, float dmgmod, float MaxHp, float speed, float MaxMana);
	void takedmg(int x);
	float gethp();
	int getweaponval();
	int getarmorval();
	bool getblocking();
	virtual float Execute_skill(Entity* Enemy, int choice);
	void damage(int x);



};
