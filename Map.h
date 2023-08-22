#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <Windows.h>

#include "Utility.h"

class Map
{
private:
	COORD Player_Pos;
	COORD Screen;
	COORD max_Size = GetLargestConsoleWindowSize(outputHandle);
	CONSOLE_SCREEN_BUFFER_INFO CSBI;

	int W, H;
	int MapNo;
	std::vector<std::vector<char>> mapVector;
public:
	void GenerateGrid() const;
	void Move(const int posX, const int posY);
	void UpdatePlayer() const;

	void checkNPC() const;

	Map(int mapID);
};

