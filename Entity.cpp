#include<iostream>
#include "Entity.h"
Entity::Entity()
{
}
Entity::Entity(std::string name,float dmgmod, float MaxHp, float speed, float MaxMana)
{
	this->name = name;
	Hp=this->dmgmod = dmgmod;
	this->MaxHp = MaxHp;
	this->speed = speed;
	mana=this->MaxMana = MaxMana;
	skills.push_back({ "Heal"," ", 5, 4,false,false,true });
	skills.push_back({ "Slash"," ", 0, 3,false,false,false });
}
void Entity::takedmg(int x)
{
	if (x > 0) {
		Hp = Hp - x;
	};
}
float Entity::gethp()
{
	return Hp;
}
int Entity::getweaponval()
{
	if (weapon != nullptr) {
		return weapon->get_addpt();
	}
	else {
		return 0;
	}
}
int Entity::getarmorval()
{
	if (armor != nullptr) {
		return armor->get_addpt();
	}
	else {
		return 0;
	}
}
bool Entity::getblocking()
{
	return blocking;
}
float Entity::Execute_skill(Entity* Enemy, int choice)
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
			return (skills[choice].base * dmgmod);
		}
		else {
			Enemy->takedmg(Enemy->gethp() - ((skills[choice].base * dmgmod * (Enemy->getblocking() ? 0.5f : 1)))-Enemy->getarmorval()+getweaponval());
			return (skills[choice].base * dmgmod * (Enemy->getblocking() ? 0.5f : 1));
		}
	
}

void Entity::damage(int x)
{
}

