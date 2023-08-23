#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <Windows.h>

#include "Utility.h"

enum Maps
{
	WORLD,
	DETECTIVE_ROOM,
	LIBRARY,
	LIBRARY_FORBIDDEN,
	SHOP,
	STRENGTH_HOUSE,
	LUCK_HOUSE,
};

enum Doors
{
	//WORLD
	WORLD_DETECTIVE_ROOM = 1,
	WORLD_LIBRARY = 2,
	WORLD_SHOP = 4,
	WORLD_STR = 5,
	WORLD_LUK = 6,

	//LIBRARY
	LIBRARYFORBIDDEN = 3,
};

enum NPCS
{
	CEDRIC_EVERHART,
	GENERAL_MARCUS,
	ISABELLA_NIGHTSHADE,
	VALERIA_STORMBRINGER,
	AURELIUS_MINDWEAVER,
	SERAPHINA_FORTUNA,
};

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

	int currentDoor;
public:
	void GenerateGrid() const;
	void Move(const int posX, const int posY);
	void UpdatePlayer() const;

	int getCurrentDoor(void) const;

	bool checkObject(std::string Type);
	bool checkNPC() const;

	void setMap(int mapID);

	Map();
};