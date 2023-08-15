#include "Player.h"
#include<iostream>
#include<conio.h>
#include <windows.h>

Player::Player(float csmod[6], std::string Name)
{
	this->name = name;
	for (int i = 0; i < 6; i++) {
		this->csmod[i] = csmod[i];
	}
	statcalc();
	Hp = MaxHp;
	mana = MaxMana;
	skills.push_back({ "\033[1;33mShield bash\033[0m","A well rounded maneuver that blocks and deals damage.", 5, 4,false,false,true });
	skills.push_back({ "\033[1;32mMeditate\033[0m","Heals hp and blocks.", 50, 15 ,true,true,false });
	skills.push_back({ "\033[1;31mBerzerk blade\033[0m","High damage and high cost slash.", 10, 15 ,false,false,false });
}

int Player::Playerturn(Entity* Enemy)
{
	while (1) {
		std::cout << "\033[1;36m> You ran into a FIGHT Grid and bumped into an ENEMY!\033[0m" << std::endl;

		std::cout << "A " << "\033[1;35m" << Enemy->getname() << "\033[0m" << " approaches you menacingly!" << std::endl;
		std::cout << Enemy->getname() << "'s \033[1;31m[HP] > \033[0m" << Enemy->gethp() << std::endl;
		std::cout << "Your \033[1;31m[HP] > \033[0m" << Hp << " " << "\033[1;36m[MANA] > \033[0m" << mana << std::endl;
		std::cout << "It's YOUR turn. What will you do?" << std::endl;

		std::cout << " " << std::endl;
		std::cout << " " << std::endl;
		for (int i = 0; i < skills.size(); i++)//prints amount relative to number of skills
		{
			std::cout << skills[i].name;
			if (i == scrollwheelpos) {
				std::cout << "\033[1;31m <-\033[0m" << std::endl;//for generating pointer
			}
			else { std::cout << std::endl; }
			std::cout << skills[i].description << " cost:" << skills[i].cost << (skills[i].manacost ? "mana " : " hp ") << (skills[i].healing ? "heals: " : "deals: ") << skills[i].base << std::endl;
		
			if (GetAsyncKeyState('W')) // for controlling pointer
			{
				if (scrollwheelpos <= 0) {
					scrollwheelpos = (skills.size() - 1);
				}
				else
				{
					scrollwheelpos--;
				}
				Sleep(1);
				system("cls");
			}
			 if (GetAsyncKeyState('S'))
			{

				if (scrollwheelpos > (skills.size() - 2)) {
					scrollwheelpos = 0;
				}
				else
				{
					scrollwheelpos++;
					Sleep(1);
					system("cls");
				}
			}
			 if (GetAsyncKeyState('X')) {
				 return scrollwheelpos;
			 }

		}
		std::cout << "\033[1;36mUse the [W] and [S] Keys to toggle between skills. [X] to Select skill.\033[0m";
		Sleep(100);
		system("cls");
	}
}

void Player::statcalc()
{
	// 0 is str , 1 is dex , 2 is int , 3 is vit , 4 is lck , 5 is wis 

	for (int i = 0; i < 6; i++) {
		characterbase[i] = (10 + cslvl[i]) * csmod[i];
	}
	//hp calculations
	MaxHp = (characterbase[3] * 0.8f) + (characterbase[4] * 0.6f) + (characterbase[5] * 0.4f);
	//mana calc
	MaxMana = (characterbase[2] * 5) + (characterbase[5] * 10);

	//damage caluclations
	dmgmod = log10(characterbase[0] + (characterbase[1] * 0.5f) + characterbase[8]);
	//speed calculations
	speed = log10((characterbase[1] * 1.5f) + (characterbase[0] * 0.8f) + 5);//log is used inorder to prevent modifiers from becoming too high
	//magic modifier
	magicmod = log10(characterbase[2] + (characterbase[5] * 0.5f) + characterbase[8]);
}
int Player::getskillcount()
{
	return skills.size();
}
void Player::displayskills(int i)
{
	
 std::cout << skills[i].description << " cost:" << skills[i].cost << (skills[i].manacost ? "mana " : " hp ") << (skills[i].healing ? "heals: " : "deals: ") << skills[i].base << std::endl;

	
}