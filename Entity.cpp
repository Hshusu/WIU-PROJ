#include<iostream>

#include "Entity.h"
#include "AttackGame.h"

void Entity::takedmg(int x)
{
	Hp = Hp - x;
	if (Hp < 1) {
		Hp = 0;
	};
}
std::string Entity::getname()
{
	return name;
}
float Entity::gethp()
{
	return Hp;
}
float Entity::getMaxHP()
{
	return MaxHp;
}
float Entity::GetCR()
{
	return CR;
}
float Entity::getmana()
{
	return mana;
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
int Entity::getWeakness()
{
	return Weakness;
}
int Entity::getRes()
{
	return Res;
}
void Entity::CrCHange(int x)
{
	CR = CR - x;
	if (CR < 0) {
		CR = 0;
	};
}
bool Entity::getturn()
{
	return turn;
}
void Entity::setturn(bool x)
{
	turn = x;
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
float Entity::getspeed()
{
	return speed;
}
bool Entity::CrCheck()
{
	CR = CR + (1 * speed);
	if (CR >= 100) {
		CR = 0;
		turn = true;
		return true;
	}
	else {
		return false;
	}
}
void Entity::Execute_skill(Entity* Enemy, int choice)
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
			std::cout << name << " used " << skills[choice].name << " on itself"<<std::endl ;
		}
		else {
			if (skills[choice].Element == Enemy->getWeakness()) {
				Enemy->CrCHange(50);
				setdmgB4game(((skills[choice].base * dmgmod * 1.5 * (Enemy->getblocking() ? 0.5f : 1))) - Enemy->getarmorval() + getweaponval());
				
				Enemy->takedmg(((skills[choice].base * dmgmod *1.5* (Enemy->getblocking() ? 0.5f : 1))) - Enemy->getarmorval() + getweaponval());
				std::cout << name << " used " << skills[choice].name << " on " << Enemy->getname() << " dealing " << abs((skills[choice].base * dmgmod*1.5 * (Enemy->getblocking() ? 0.5f : 1)) - Enemy->getarmorval() + getweaponval()) << std::endl;
				std::cout << "it did critical damage!!   Pushing the enemies turn back" << std::endl;

			}
			else if((skills[choice].Element == Enemy->getRes())) {
				Enemy->takedmg(((skills[choice].base * dmgmod * 0.5 * (Enemy->getblocking() ? 0.5f : 1))) - Enemy->getarmorval() + getweaponval());
				std::cout << name << " used " << skills[choice].name << " on " << Enemy->getname() << " dealing " << abs((skills[choice].base * dmgmod * 1.5 * (Enemy->getblocking() ? 0.5f : 1)) - Enemy->getarmorval() + getweaponval()) << std::endl;
				std::cout << "it did low damage......" << std::endl;
			}
			else {
				setdmgB4game(((skills[choice].base * dmgmod * (Enemy->getblocking() ? 0.5f : 1))) - Enemy->getarmorval() + getweaponval());
				AttackGame();
				Enemy->takedmg(((skills[choice].base * dmgmod * (Enemy->getblocking() ? 0.5f : 1))) - Enemy->getarmorval() + getweaponval());
				std::cout << name << " used " << skills[choice].name << " on " << Enemy->getname() << " dealing " << abs((skills[choice].base * dmgmod * (Enemy->getblocking() ? 0.5f : 1)) - Enemy->getarmorval() + getweaponval()) << std::endl;
			}
			}

	
}

void Entity::setdmgB4game(float dmg)
{
	dmgB4game = dmg;
}

float Entity::getdmgB4game(void)
{
	return dmgB4game;
}

void Entity::damage(int x)
{

}

