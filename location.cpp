#include "location.h"
int location::getx() const {
	return x;
} 
int location::gety() const {
	return y;
}

void location::setx(const int x)
{
	this->x = x;
}

void location::sety(const int y)
{
	this->y = y;
}
