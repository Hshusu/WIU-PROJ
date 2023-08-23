#pragma once
#include<Windows.h>
#include <vector>
#include"Item.h"
class inventory
{
private:
	COORD pointer;
	int scroll = 20;
	int scrollmax = 0;
	std::vector<std::vector<int>> InventoryVector;
public:
	inventory(int x, int y);
	void Move(const int posX, const int posY, Item current);
	void RenderInventory(Item current);
	void RenderInventory();
	bool placeitem(Item current);
	void movescroll(int x);
	void setscroll(int x);
	int getscroll();
	void setmaxscroll(int x);
	int getmaxscroll();
	int discard(int x);
};
