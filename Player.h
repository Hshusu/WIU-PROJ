#pragma once
#include "Entity.h"
class Player: public Entity
{
private:
	// 0 is str , 1 is dex , 2 is int , 3 is vit , 4 is lck , 5 is wis 
	float characterbase[6]{ 10 ,10,10,10,10,10};
	float csmod[6]{ 0, 0, 0, 0, 0, 0 };
	int cslvl[6]{ 0, 0, 0, 0, 0, 0 };
public:

	Player(float csmod[8], std::string Name);
	void statcalc();
	int getskillcount();
	void displayskills(int i);
};

