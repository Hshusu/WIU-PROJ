#pragma once
#include "location.h"
#include <iostream>
#include <vector>

class scene
{
private:
	location playerpos;
	int W, H;
	std::vector<std::vector<char>> map;
	int SceneNo;
public:
	scene(int x);
	void gridgen()const;
	void plrgen()const;
	void plrupdate()const;
	void move(const int x, const int y);
};

