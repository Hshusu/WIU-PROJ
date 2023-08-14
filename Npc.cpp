#include "Npc.h"
#include <random>
int Npc::chooseaction()
{
	std::random_device rdm;
	std::uniform_int_distribution<int> dist(1, 100);
	int enemychoice = (dist(rdm) - 40);//done to reduce chance of healing
	//for healing
	if ((100 * (Hp / MaxHp)) <= enemychoice) {//makes enemy heal more when at low hp
		//heal used

		return 0;
		//place holder is used because enemy does not have manavalues
	}
	else {
		return 1;
	}
}
