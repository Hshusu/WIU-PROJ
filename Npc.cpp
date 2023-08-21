#include "NPC.h"
#include <random>

int NPC::ChooseAction()
{
	int enemyChoice = (Utility::randomNumber(1, 100)); //Done to reduce chance of healing

	//For Healing
	if ((100 * (HP / MaxHp)) <= enemyChoice) {//makes enemy heal more when at low hp
		//Heal used

		return 0;
		//Placeholder is used because enemy does not have Mana values
	}
	else {
		return 1;
	}
}

NPC::NPC(std::string Name, float DMGModifier, float MaxHp, float Speed, float MaxMana, int Weak, int Res)
{
	Weakness = Weak;
	Resistance = Res;
	this->Name = Name;
	this->DMGModifier = DMGModifier;
	HP = this->MaxHp = MaxHp;
	this->speed = speed;
	Mana = this->MaxMana = MaxMana;
	Skills.push_back({ "Heal", " ", 5, 4, true, true, false });
	Skills.push_back({ "Slash", " ", 0, 3, false, false, false });
}