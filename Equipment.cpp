#include "Equipment.h"
#include<iostream>
#include <random>

Equipment::Equipment(int const low)
{
	std::random_device rdm;
	std::uniform_int_distribution<int> dist(low, 10);
	addpt = dist(rdm);

}

Equipment::~Equipment()
{

}

int Equipment::get_addpt()
{
	return addpt;
}
