#include "Player.h"
#include<iostream>
#include<conio.h>
#include <windows.h>
#include "AttackGame.h"

Player::Player(float csmod[6], std::string Name, int Weak, int res)
{
	Weakness = Weak;
	Res = res;
	this->name = name;
	for (int i = 0; i < 6; i++) {
		this->csmod[i] = csmod[i];
	}
	statcalc();
	Hp = MaxHp;
	mana = MaxMana;
	skills.push_back({ "\033[1;33mShield bash\033[0m","A well rounded maneuver that blocks and deals damage.", 5, 4,false,false,true ,None,0});
	skills.push_back({ "\033[1;32mMeditate\033[0m","Heals hp and blocks. Also advances turn by 50%", 50, 15 ,true,true,false,Healing ,-50});
	skills.push_back({ "\033[1;31mBerzerk blade\033[0m","High damage and high cost slash.", 10, 15 ,false,false,false,Fire,0 });
}
//Fire,
//Ice,
//Lightning,
//Wind,
//Darkness,
//Siphon,
//None,
void Player::Uigen(Entity Enemy)
{
	std::cout << "\033[1;36m> You ran into a FIGHT Grid and bumped into an ENEMY!\033[0m" << std::endl;

	std::cout << "A " << "\033[1;35m" << Enemy.getname() << "\033[0m" << " approaches you menacingly!" << std::endl;
	std::cout << Enemy.getname() << "'s \033[1;31m[HP] > \033[0m" << Enemy.gethp() << "   they are weak to :"; 
	switch (Enemy.getWeakness())
	{
	case Fire:
		std::cout << "\033[1;31mFire\033[0m";
		break;
	case Ice:
		std::cout << "\033[1;34mIce\033[0m";
		break;
	case Lightning:
		std::cout << "\033[0;33mLightning\033[0m";
		break;
	case Wind:
		std::cout << "\033[0;32mWind\033[0m";
		break;
	case Darkness:
		std::cout << "\033[0;35mDarkness\033[0m";
		break;
	case Siphon:
		std::cout << "Siphon";
		break;

	default:
		std::cout << "Nothing!!";
		break;
	}
	std::cout << std::endl << " They are Resistant to  : ";
	switch (Enemy.getRes())
	{
	case Fire:
		std::cout << "\033[1;31mFire\033[0m";
		break;
	case Ice:
		std::cout << "\033[1;34mIce\033[0m";
		break;
	case Lightning:
		std::cout << "\033[0;33mLightning\033[0m";
		break;
	case Wind:
		std::cout << "\033[0;32mWind\033[0m";
		break;
	case Darkness:
		std::cout << "\033[0;35mDarkness\033[0m";
		break;
	case Siphon:
		std::cout << "Siphon";
		break;

	default:
		std::cout << "Nothing!!";
		break;
	}
	std::cout << std::endl;
	std::cout << "Your \033[1;31m[HP] > \033[0m" << Hp << " " << "\033[1;36m[MANA] > \033[0m" << mana << std::endl;
	std::cout << "It's YOUR turn. What will you do?" << std::endl;

	std::cout << " " << std::endl;
	std::cout << " " << std::endl;	
			int pos;
			std::cout << "\033[1;36m> You ran into a FIGHT Grid and bumped into an ENEMY!\033[0m" << std::endl;

			std::cout << "A " << "\033[1;35m" << Enemy.getname() << "\033[0m" << " approaches you menacingly!" << std::endl;
			std::cout << Enemy.getname() << "'s \033[1;31m[HP] > \033[0m" << Enemy.gethp() << " CR is :" << int(Enemy.GetCR()) << std::endl;
			int barWidth = 70;

			std::cout << "[";
			pos = barWidth * Enemy.gethp() / Enemy.getMaxHP();
			for (int i = 0; i < barWidth; ++i) {
				if (i < pos) std::cout << "\033[1;32m=\033[0m";
				else if (i == pos) std::cout << "\033[1;32m>\033[0m";
				else std::cout << " ";
			}
			std::cout << "] " << int(Enemy.gethp());
			std::cout.flush();
			std::cout << std::endl;
			std::cout << "[";
			pos = barWidth * 0.01 * Enemy.GetCR();
			for (int i = 0; i < barWidth; ++i) {
				if (i < pos) std::cout << "=";
				else if (i == pos) std::cout << ">";
				else std::cout << " ";
			}
			std::cout << "] " << int(Enemy.GetCR()) << " %\r";
			std::cout.flush();

			std::cout << std::endl;
			std::cout << "Your \033[1;31m[HP] > \033[0m" << Hp << " " << "\033[1;36m[MANA] > \033[0m" << mana << " CR is :" << CR << std::endl;
			std::cout << std::endl;

			std::cout << "[";
			pos = barWidth * Hp / MaxHp;
			for (int i = 0; i < barWidth; ++i) {
				if (i < pos) std::cout << "\033[1;32m=\033[0m";
				else if (i == pos) std::cout << "\033[1;32m>\033[0m";
				else std::cout << " ";
			}
			std::cout << "] " << int(Hp);
			std::cout.flush();
			std::cout << std::endl;
			std::cout << "[";
			if (CR == 0) 
			{ pos = barWidth * 1; }
			else { pos = barWidth * CR/100; }
			for (int i = 0; i < barWidth; ++i) {
				if (i < pos) std::cout << "=";
				else if (i == pos) std::cout << ">";
				else std::cout << " ";
			}
			if (CR == 0) { std::cout << "] " << 100 << " %\r"; }
			else { std::cout << "] " << int(CR) << " %\r"; }
			std::cout.flush();

			std::cout << std::endl;

			std::cout << "It's YOUR turn. What will you do?" << std::endl;

			std::cout << " " << std::endl;
			std::cout << " " << std::endl;
}

int Player::Playerturn(Entity* Enemy)
{

	Uigen(*Enemy);
	for (int i = 0; i < skills.size(); i++)//prints amount relative to number of skills
	{
		std::cout << skills[i].name;
		if (i == scrollwheelpos) {
			std::cout << "\033[1;31m <-\033[0m" << std::endl;//for generating pointer
		}
		else { std::cout << std::endl; }
		std::cout << skills[i].description << " cost:" << skills[i].cost << (skills[i].manacost ? "mana " : " hp ") << (skills[i].healing ? "heals: " : "deals: ") << skills[i].base << std::endl;


	}
	std::cout << "\033[1;36mUse the [W] and [S] Keys to toggle between skills. [X] to Select skill.\033[0m";
	while (1) 
	{
		if ((GetAsyncKeyState('W')) || (GetAsyncKeyState('S')) || (GetAsyncKeyState('X'))) {

			system("cls");
			Uigen(*Enemy);
			if (GetAsyncKeyState('W')) // for controlling pointer
			{
				if (scrollwheelpos <= 0) {
					scrollwheelpos = (skills.size() - 1);
				}
				else
				{
					scrollwheelpos--;
				}
			}
			if (GetAsyncKeyState('S'))
			{

				if (scrollwheelpos > (skills.size() - 2)) {
					scrollwheelpos = 0;
				}
				else
				{
					scrollwheelpos++;

				}
			}
			if (GetAsyncKeyState('X')) 
			{
				return scrollwheelpos;
			}

			for (int i = 0; i < skills.size(); i++)//prints amount relative to number of skills
			{
				std::cout << skills[i].name;
				if (i == scrollwheelpos) {
					std::cout << "\033[1;31m <-\033[0m" << std::endl;//for generating pointer
				}
				else { std::cout << std::endl; }
				std::cout << skills[i].description << " cost:" << skills[i].cost << (skills[i].manacost ? "mana " : " hp ") << (skills[i].healing ? "heals: " : "deals: ") << skills[i].base << std::endl;


			}
			std::cout << "\033[1;36mUse the [W] and [S] Keys to toggle between skills. [X] to Select skill.\033[0m";
			Sleep(100 );
		}
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
	dmgmod = log10(characterbase[0] + (characterbase[1] * 0.5f));
	//speed calculations
	speed = log10((characterbase[1] * 1.5f) + (characterbase[0] * 0.8f) + 5);//log is used inorder to prevent modifiers from becoming too high
	//magic modifier
	magicmod = log10(characterbase[2] + (characterbase[5] * 0.5f) );
}

int Player::getskillcount()
{
	return skills.size();
}

void Player::displayskills(int i)
{
	
 std::cout << skills[i].description << " cost:" << skills[i].cost << (skills[i].manacost ? "mana " : " hp ") << (skills[i].healing ? "heals: " : "deals: ") << skills[i].base << std::endl;


}

void Player::Execute_skill(Entity* Enemy, int choice)
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
		AttackGame attackgame;
		float healingamt = Hp + (skills[choice].base * dmgmod) * attackgame.GetdmgModifier();
		Hp = healingamt;
		//for checking if hp is over maximum
		if (Hp > MaxHp) {
			Hp = MaxHp;
		}
		std::cout << name << " used " << skills[choice].name << " on itself " << std::endl;
		std::cout << "healed for " << healingamt << std::endl;
	}
	else
	{
		if (skills[choice].Element == Enemy->getWeakness()) {
			Enemy->CrCHange(50);
			AttackGame attackgame;
			dmg = skills[choice].base * dmgmod * 1.5 * (Enemy->getblocking() ? 0.5f : 1) - Enemy->getarmorval() + getweaponval();
			float finalDmg = dmg * attackgame.GetdmgModifier();
			Enemy->takedmg(finalDmg);
			std::cout << name << " used " << skills[choice].name << " on " << Enemy->getname() << " dealing " << abs(finalDmg) << std::endl;
			std::cout << "it did critical damage!!   Pushing the enemies turn back" << std::endl;

		}
		else if ((skills[choice].Element == Enemy->getRes())) 
		{
			AttackGame attackgame;
			dmg = skills[choice].base * dmgmod * 0.5 * (Enemy->getblocking() ? 0.5f : 1) - Enemy->getarmorval() + getweaponval();
			float finalDmg = dmg * attackgame.GetdmgModifier();
			Enemy->takedmg(finalDmg);
			std::cout << name << " used " << skills[choice].name << " on " << Enemy->getname() << " dealing " << abs(finalDmg) << std::endl;
			std::cout << "it did low damage......" << std::endl;
		}
		else
		{
			AttackGame attackgame;
			dmg = skills[choice].base * dmgmod * (Enemy->getblocking() ? 0.5f : 1) - Enemy->getarmorval() + getweaponval();
			float finalDmg = dmg * attackgame.GetdmgModifier();
			Enemy->takedmg(finalDmg);
			std::cout << name << " used " << skills[choice].name << " on " << Enemy->getname() << " dealing " << abs(finalDmg) << std::endl;
		}
	}
}

void Player::setDmg(int dmg)
{
	dmg = dmg;
}

int Player::getDmg(void)
{
	return dmg;
}