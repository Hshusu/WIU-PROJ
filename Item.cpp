#include"Item.h"
Item::Item(int height, int width, std::string Name, int ID)
{
	this->height = height;
	this->width = width;
	this->Name = Name;
	this->ID = ID;
}
int Item::getWidth(void) {
	return width;
}
int Item::getID()
{
	return ID;
}
int Item::getHeight(void) {
	return height;
}

std::string Item::getName(void) {
	return Name;
}
void Item::setheight(int height) {
	this->height = height;
}
void Item::setwidth(int width) {
	this->width = width;
}
void Item::setpos(int x, int y)
{
	pos.X = x;
	pos.Y = y;
}
void Item::rotate()
{
	width = width + height;
	height = width - height;
	width = width - height;
}
void Item::place()
{
	placed = true;
}
bool Item::getplaced()
{
	return placed;
}
void Item::setName(std::string Name) {
	this->Name = Name;
}
