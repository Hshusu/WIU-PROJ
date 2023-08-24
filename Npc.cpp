#include "NPC.h"
#include <random>

int NPC::ChooseAction()
{
	int enemyChoice = (Utility::randomNumber(1, 100)); //Done to reduce chance of healing

	//For Healing 
	if (this->Name == "Isabella Nightshade [Reptilian]") {
	
		if ((100 * (HP / MaxHp)) <= enemyChoice-80) {//makes enemy heal more when at low hp
			//Heal used

			return 4;
			//Placeholder is used because enemy does not have Mana values
		}
		else if ((100 * (HP / MaxHp)) <= enemyChoice) {//makes enemy heal more when at low hp
			//Heal used
			if (enemyChoice % 2 == 0) {

				return 0;
			}
			else { return 1; }
			
			//Placeholder is used because enemy does not have Mana values
		}
		else {
			//start dodge minigame

			Dodge obstaclecollided;
			obstaclecollided.startGame();

			if (enemyChoice % 2 == 0) {

				return 2;
			}
			else { return 3; }
		}
	}

	if ((100 * (HP / MaxHp)) <= enemyChoice) {//makes enemy heal more when at low hp
		//Heal used

		return 0;
		//Placeholder is used because enemy does not have Mana values
	}
	else {
		//start dodge minigame

		Dodge obstaclecollided;
		obstaclecollided.startGame();

		return 1;
	}
}

void NPC::displaystats()
{
	system("cls");
	std::cout << Name;
	std::cout << std::endl;
	std::cout << "Weakness :"<< Weakness;
	std::cout << std::endl;
	std::cout << "Resistance :" << Resistance;
	std::cout << std::endl;
	std::cout << "Hp :" << MaxHp;
	std::cout << std::endl;
	int size = Skills.size();
	std::cout << " skills :" << std::endl;
		for (int i = 0; i < size; i++) {
			std::cout << Skills[i].Name;
			std::cout << std::endl;
			std::cout << Skills[i].Description;
			std::cout << std::endl;
	}

}

NPC::NPC(std::string Name, float DMGModifier, float MaxHp, float Speed, float MaxMana, int Weak, int Res)
{
	Weakness = Weak;
	Resistance = Res;
	this->Name = Name;
	this->DMGModifier = DMGModifier;
	HP = this->MaxHp = MaxHp;
	this->speed = Speed;
	Mana = this->MaxMana = MaxMana;
	if (this->Name == "Isabella Nightshade [Reptilian]") {
		Armor = new Equipment(5,0);
		Weapon = new Equipment(5,0);
		Skills.push_back({ "Galaxyia heal", "Uses the power of the enchiridion to heal greatly while blocking", 10, 10, true, true, false,false });
		Skills.push_back({ "Reptilian accelertation", "nightshade's Reptilian blood allows her to heal slightly, forwarding turn as well", 5, 10, true, false, false,false,None,30 });
		Skills.push_back({ "Magic blast", "Harnesses the power of the enchiridion to fire a burst of energy dealing medium damage and advancing her turn ", 5, 6, true, false, false,false ,Fire ,20});
		Skills.push_back({ "enhanced claw slash", "Using the dark powers nightshade coats her claws in ice and slashes, dealing ice damage", 8,7, false, false, false,false ,Darkness });
		Skills.push_back({ "Collapsing universe", "Collapses a universe using the power of the enchiridion dealing high damage", 20, 15, false, false, false,false ,Darkness});
	}
	else {
		Armor = new Equipment(1);
		Weapon = new Equipment(1);
		Skills.push_back({ "Heal", " ", 5, 4, true, true, false });
		Skills.push_back({ "punch", " ", 0, 3, false, false, false });
	}
}



