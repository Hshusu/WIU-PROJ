#include "Entity.h"

std::string Entity::getName()
{
	return Name;
}

float Entity::getSpeed()
{
	return speed;
}

float Entity::getHP()
{
	return HP;
}

float Entity::getMaxHP()
{
	return MaxHp;
}

void Entity::resethp()
{
	HP = MaxHp;
}

float Entity::getCR()
{
	return CombatReady;
}

float Entity::getMana()
{
	return Mana;
}

int Entity::getWeakness()
{
	return Weakness;
}

int Entity::getResistance()
{
	return Resistance;
}

bool Entity::getBlocking()
{
	return Blocking;
}

int Entity::getWeaponVal()
{
	if (Weapon != nullptr) {
		return Weapon->getEquipmentAddifier();
	}
	else {
		return 0;
	}
}

int Entity::getArmorVal()
{
	if (Armor != nullptr) {
		return Armor->getEquipmentAddifier();
	}
	else {
		return 0;
	}
}

//
bool Entity::CheckCR()
{

	CombatReady = CombatReady + (1 * speed);
	if (CombatReady >= 100) {
		CombatReady = 0;
		Turn = true;
		
		return true;
	}
	else {
		return false;
	}
}

void Entity::UpdateCR(int newCR)
{
	CombatReady = CombatReady - newCR;
	if (CombatReady < 0) {
		CombatReady = 0;
	};
}

//
bool Entity::getTurn()
{
	return Turn;
}

void Entity::setTurn(bool Go)
{
	Turn = Go;
}

//
void Entity::TakeDMG(int Damage)
{
	HP = HP - Damage;
	if (HP < 1) {
		HP = 0;
	};
}

void Entity::ExecuteSkill(Entity* Enemy, int Choice)
{

	if (Skills[Choice].Blocking) {
		Blocking = true;
	}
	if (((Skills[Choice].Healing == true) || (Skills[Choice].ManaCost == true)) && (Mana > (Skills[Choice].Cost))) {
		Mana = Mana - Skills[Choice].Cost;
	}
	else {
		HP = HP - Skills[Choice].Cost;
	}
	if (Skills[Choice].Healing == true)
	{
		HP = HP + (Skills[Choice].Base * DMGModifier);
		//For checking if HP is over maximum
		if (HP > MaxHp) {
			HP = MaxHp;
		}
		std::cout << Name << " used " << Skills[Choice].Name << " on themself!" << std::endl;
	}
	else {
		if (Skills[Choice].Element == Enemy->getWeakness()) {
			Enemy->UpdateCR(50);
			Enemy->TakeDMG(((Skills[Choice].Base * DMGModifier * 1.5 * (Enemy->getBlocking() ? 0.5f : 1))) - Enemy->getArmorVal() + getWeaponVal());
			std::cout << Name << " used " << Skills[Choice].Name << " on " << Enemy->getName() << " dealing " << abs((Skills[Choice].Base * DMGModifier * 1.5 * (Enemy->getBlocking() ? 0.5f : 1)) - Enemy->getArmorVal() + getWeaponVal()) << std::endl;
			std::cout << "it did critical damage!! Pushing the enemies turn back" << std::endl;

		}
		else if ((Skills[Choice].Element == Enemy->getResistance())) {
			Enemy->TakeDMG(((Skills[Choice].Base * DMGModifier * 0.5 * (Enemy->getBlocking() ? 0.5f : 1))) - Enemy->getArmorVal() + getWeaponVal());
			std::cout << Name << " used " << Skills[Choice].Name << " on " << Enemy->getName() << " dealing " << abs((Skills[Choice].Base * DMGModifier * 1.5 * (Enemy->getBlocking() ? 0.5f : 1)) - Enemy->getArmorVal() + getWeaponVal()) << std::endl;
			std::cout << "it did low damage..." << std::endl;
		}
		else
		{


			if (Dodge::enemyCollided == true)
			{
			
				Enemy->TakeDMG(((Skills[Choice].Base * DMGModifier * (Enemy->getBlocking() ? 0.5f : 1))) - Enemy->getArmorVal() + getArmorVal());
				std::cout << Name << " used " << Skills[Choice].Name << " on " << Enemy->getName() << " dealing " << abs((Skills[Choice].Base * DMGModifier * (Enemy->getBlocking() ? 0.5f : 1)) - Enemy->getArmorVal() + getWeaponVal()) << std::endl;

			}
			else if (Dodge::enemyCollided == false)
			{
				Enemy->TakeDMG(0);
				std::cout << Name << " used " << Skills[Choice].Name << " on " << Enemy->getName() << " dealing  0" << std::endl;


			}



		}
	}


}




 