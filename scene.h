#pragma once
#include "location.h"
#include <iostream>
#include <vector>
#include <Windows.h>
class scene
{
private:
	location playerpos;
	int W, H;
	std::vector<std::vector<char>> map;
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD max_size = GetLargestConsoleWindowSize(screen);
	int SceneNo;
public:
	scene(int x);
	void gridgen()const;
	void plrgen()const;
	void plrupdate()const;
	void checkNPC()const;
	void move(const int x, const int y);
};

