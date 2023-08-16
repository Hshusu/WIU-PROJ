#include "scene.h"
#include <stdio.h>
#include <Windows.h>
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void scene::move(const int x, const int y) {
	if ((map[playerpos.gety() + y][playerpos.getx() + x]) == '.') {
		playerpos.sety(playerpos.gety() + y);
		if (playerpos.gety() < 0) {
			playerpos.sety(0);
		}
		if (playerpos.gety() > H - 1) {
			playerpos.sety(H - 1);
		}
		playerpos.setx(playerpos.getx() + x);
		if (playerpos.getx() < 0) {
			playerpos.setx(0);
		}
		if (playerpos.getx() > W - 1) {
			playerpos.setx(W - 1);
		}
	}
}



scene::scene(int x)
{

	switch (x)
	{
		//Outdoor Maps
		//World Map (A General Map thats like a top down view of a city (Library, Shop, House...)
		// 
		//Indoor Maps
		//Lobby/Spawn (Area where detective (YOU) Spawn in to select your party members)
		//Interrogation Room (Where the Police are interrogating the suspect)
		//Library Receptionist (Where you meet the Librarian)
		//Library Book Section (Just a random part of the Library. Explore for clues, will bump into forbidden area at the edge)
		//Library Forbidden Section
		//Important Person House Room 1
		//Important Person House Room 2
		//Important Person House Room 3
		//Shop

	case 1:
		// world map
		map = {
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
		{'#','#','#','#','-','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','#','L','.','.','.','.','.','D','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','|','.','.','.','.','.','.','.','.','.','.','.','.','*','^','*','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','{','M','}','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','_','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','/','_','_','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','-','-','-','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','S','|','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','-','-','-','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','H','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','[','.','.','.',']','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','|','<','g','>','|','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','|','_','_','_','|','.','.','.','.','.','.','#',},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
		};
		break;
	case 2:
		//reception room
		map = {
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','|','C','|','.','^','.','.','.','#',},
		{'#','.','.','.','.','.','.','[','-',']','.','|','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','_','.','.','.','#',},
		{'#','.','.','.','.','-','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.',']','|','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.',']','|','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','-','.','.','.','.','.','.','.','.','.','I',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','#','#','#','#','#','D','O','O','R','#','#','#','#','#','#',},
		};
	case 3:
		//reception room
		map = {
		{'#','#','#','#','#',},
		{'#','.','.','.','#',},
		{'#','.','F','.','#',},
		{'#','.','.','.','#',},
		{'#','.','.','.','#',},
		{'#','.','.','.','#',},
		{'#','.','.','.','#',},
		{'#','.','.','.','#',},
		{'#','.','.','.','#',},
		{'#','#','D','#','#',},
		};
	default:
		break;
	}
	H = map.size();
	W = map[0].size();
	playerpos.sety(H/2);
	playerpos.setx(W/2);
}

void scene::gridgen()const
{
	
	COORD zone1_Coords = { max_size.X / 2 - (playerpos.getx() * 3), max_size.Y / 2 - playerpos.gety() };
	SetConsoleCursorPosition(h, zone1_Coords);
	for (int col = 0; col < H; col++)
	{
		for (int row = 0; row < W; row++)
		{
				std::cout << map[col][row] << "  ";

		}
		zone1_Coords.Y++;
		SetConsoleCursorPosition(h, zone1_Coords);
	}
}

void scene::plrgen() const
{
	COORD zone1_Coords = { 7, 2 };
	SetConsoleCursorPosition(h, zone1_Coords);

	std::cout << "\033[1;35mP\033[0m";
}
//void scene::plrupdate() const
//{
//	COORD zone1_Coords = { (playerpos.getx() * 3) + 3, playerpos.gety() + 1 };
//	SetConsoleCursorPosition(h, zone1_Coords);
//	std::cout << "\033[1;35mP\033[0m";
//	COORD zone12_Coords = { 700, 2 };
//	SetConsoleCursorPosition(h, zone12_Coords);
//}
void scene::plrupdate() const
{
	COORD zone1_Coords = { max_size.X / 2 , max_size.Y / 2};
	SetConsoleCursorPosition(h, zone1_Coords);
	std::cout << "\033[1;35mP\033[0m";
	COORD zone12_Coords = { 700, 2 };
	SetConsoleCursorPosition(h, zone12_Coords);
}

void scene::checkNPC() const
{
	if ((map[playerpos.gety() + 1][playerpos.getx()]) == 'O' 
		|| (map[playerpos.gety()][playerpos.getx()] + 1) == 'O'
		|| (map[playerpos.gety() - 1][playerpos.getx()]) == 'O'
		|| (map[playerpos.gety()][playerpos.getx() - 1]) == 'O') {
		system("cls");
	}
}