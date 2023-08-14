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
	Equipment* weapon;
	Equipment* armor;
};
class Entity
{
	//PS this is pure virtual.
private:
	float dmgmod;
	float speed;
	float Hp;
	std::vector<skilldetail>skills;
public:
	Entity();
	virtual void Execute_skill(Entity* Enemy, int choice);
	void damage(int x);



};
