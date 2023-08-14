#include "Player.h"
#include<iostream>

Player::Player(float csmod[6],std::string Name)
{
	this-> name = name;
	for (int i = 0; i < 6; i++) {
		this->csmod[i] = csmod[i];
	}
	statcalc();
}

void Player::statcalc()
{
	// 0 is str , 1 is dex , 2 is int , 3 is vit , 4 is lck , 5 is wis 

	for (int i = 0; i < 6; i++) {
		characterbase[i] = (10 + cslvl[i]) * csmod[i];
	}
	//hp calculations
	Hp=MaxHp = (characterbase[3] * 0.8f) + (characterbase[4] * 0.6f) + (characterbase[5] * 0.4f);
	//mana calc
	mana=MaxMana = (characterbase[2] * 5) + (characterbase[5] * 10);

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