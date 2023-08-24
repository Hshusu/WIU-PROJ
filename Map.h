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

enum CLUES
{
	DEAD_BODY,
	CEDRIC_EVERHART_TESTIMONIAL,
	WAR_HERO_PHOTO,
	GENERAL_BLACKTHORN_TESTIMONIAL,
	MESSY_BOOKS,
	NEWSPAPERS,
	COIN,
	ISABELLA_NIGHTSHADE_TESTIMONIAL,
	VALERIA_STORMBRINGER_TESTIMONIAL,
	AURELIUS_MINDWEAVER_TESTIMONIAL,
	SERAPHINA_FORTUNA_TESTIMONIAL,
	MISSING_PAGES,
	SNAKE_SKIN
};

enum NPCS
{
	GENERAL_BLACKTHORN,
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

	std::string currentRoomText1, currentRoomText2, currentRoomText3;
	int currentClue;
	int currentDoor;

	int currentSpecialNPC;
public:
	void GenerateGrid() const;
	void Move(const int posX, const int posY, int& State, int& enemyID);
	void UpdatePlayer() const;

	std::string getCurrentRoomText1(void) const;
	std::string getCurrentRoomText2(void) const;
	std::string getCurrentRoomText3(void) const;

	int getCurrentClue(void) const;
	int getCurrentDoor(void) const;
	int getCurrentSpecialNPC(void) const;

	bool checkObject(std::string Type);
	bool checkNPC() const;
	bool checkSpecialNPC(std::string& DialogueNPC, std::string& QuestionsFileStr, std::string& ResponsesFileStr);

	void setMap(int mapID);

	Map();
};