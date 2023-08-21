#include "Npc.h"
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
		return 1;
	}
}

void Npc::Execute_skill(Entity* Enemy, int choice)
{
	if (skills[choice].blocking) {
		blocking = true;
	}
	if (((skills[choice].healing == true) || (skills[choice].manacost == true)) && (mana > (skills[choice].cost))) {
		mana = mana - skills[choice].cost;
	}
	else {
		Hp = Hp - skills[choice].cost;
	}
	if (skills[choice].healing == true)
	{
		Hp = Hp + (skills[choice].base * dmgmod);
		//for checking if hp is over maximum
		if (Hp > MaxHp) {
			Hp = MaxHp;
		}
		std::cout << name << " used " << skills[choice].name << " on itself" << std::endl;
	}
	else
	{
		if (skills[choice].Element == Enemy->getWeakness()) {
			Enemy->CrCHange(50);
			Enemy->takedmg(((skills[choice].base * dmgmod * 1.5 * (Enemy->getblocking() ? 0.5f : 1))) - Enemy->getarmorval() + getweaponval());
			std::cout << name << " used " << skills[choice].name << " on " << Enemy->getname() << " dealing " << abs((skills[choice].base * dmgmod * 1.5 * (Enemy->getblocking() ? 0.5f : 1)) - Enemy->getarmorval() + getweaponval()) << std::endl;
			std::cout << "it did critical damage!!   Pushing the enemies turn back" << std::endl;

		}
		else if ((skills[choice].Element == Enemy->getRes())) {
			Enemy->takedmg(((skills[choice].base * dmgmod * 0.5 * (Enemy->getblocking() ? 0.5f : 1))) - Enemy->getarmorval() + getweaponval());
			std::cout << name << " used " << skills[choice].name << " on " << Enemy->getname() << " dealing " << abs((skills[choice].base * dmgmod * 1.5 * (Enemy->getblocking() ? 0.5f : 1)) - Enemy->getarmorval() + getweaponval()) << std::endl;
			std::cout << "it did low damage......" << std::endl;
		}
		else
		{
			Enemy->takedmg(((skills[choice].base * dmgmod * (Enemy->getblocking() ? 0.5f : 1))) - Enemy->getarmorval() + getweaponval());
			std::cout << name << " used " << skills[choice].name << " on " << Enemy->getname() << " dealing " << abs((skills[choice].base * dmgmod * (Enemy->getblocking() ? 0.5f : 1)) - Enemy->getarmorval() + getweaponval()) << std::endl;
		}
	}
}
