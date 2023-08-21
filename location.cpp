#include "Location.h"

int Location::getLocationX() const
{
	return Location_X;
}

int Location::getLocationY() const
{
	return Location_Y;
}

void Location::setLocationX(const int LocX)
{
	Location_X = LocX;
}

void Location::setLocationY(const int LocY)
{
	Location_Y = LocY;
}
