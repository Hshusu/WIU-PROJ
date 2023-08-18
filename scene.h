#pragma once
#include "location.h"
#include <iostream>
#include <vector>
#include <Windows.h>
class scene
{
private:
	COORD playerpos;
	int W, H;
	std::vector<std::vector<char>> map;
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD max_size = GetLargestConsoleWindowSize(screen);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD scrn;


	int SceneNo;
public:
	scene(int x);
	void gridgen()const;
	void plrgen()const;
	void plrupdate()const;
	void checkNPC()const;
	void move(const int x, const int y);
};

