#pragma once
#include<vector>
#include<string>
#include"Equipment.h"

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
struct skilldetail {
	std::string name;
	std::string description; 
	int cost;
	int base;
	bool manacost;
	bool healing;
	bool blocking;
	int Element = None;
	int CrManip=0;
};
class Entity
{
protected:
	int Weakness =None;
	int Res = None;
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
	float getMaxHP();
	float GetCR();
	float getmana();
	int getweaponval();
	int getWeakness();
	int getRes();
	void CrCHange(int x);
	bool getturn();
	void setturn(bool x);
	int getarmorval();
	bool getblocking();
	float getspeed();
	bool CrCheck();
	void Execute_skill(Entity* Enemy, int choice);
	void damage(int x);



};
