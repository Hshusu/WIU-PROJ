#include "Npc.h"
#include "Dodge.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <random>

Npc::Npc(std::string name, float dmgmod, float MaxHp, float speed, float MaxMana , int Weak, int res)
{
	Weakness = Weak;
	Res = res;
	this->name = name;
	this->dmgmod = dmgmod;
	Hp=this->MaxHp = MaxHp;
	this->speed = speed;
	mana = this->MaxMana = MaxMana;
	skills.push_back({ "Heal"," ", 5, 4,false,false,true });
	skills.push_back({ "Slash"," ", 0, 3,false,false,false });
}
int Npc::chooseaction()
{		
	std::random_device rdm;
	std::uniform_int_distribution<int> dist(1, 100);
	int enemychoice = (dist(rdm) - 100);//done to reduce chance of healing
	//for healing
	if ((100 * (Hp / MaxHp)) <= enemychoice) {//makes enemy heal more when at low hp
		//heal used

		return 0;
		//place holder is used because enemy does not have manavalues
	}
	else 
	{
		Dodge Minigame;
		Minigame.startGame();

		return 1;
	}
}
