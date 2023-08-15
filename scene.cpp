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
	playerpos.sety(1);
	playerpos.setx(1);
	switch (x)
	{
	case 1:
		map = {
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
		{'#','#','#','#','#','#','D','O','O','R','#','#','#','#','#','#',},
		};
		H = map.size();
		W = map[0].size();
		break;
	default:
		break;
	}

}

void scene::gridgen()const
{
	int Counter = 0;
	COORD zone1_Coords = { 3, 1 };
	SetConsoleCursorPosition(h, zone1_Coords);
	for (int col = 0; col < H; col++)
	{
		for (int row = 0; row < W; row++)
		{
			std::cout << map[col][row] << "   ";
			Counter++;
		}
		if (Counter == 16)
		{
			Counter = 0;
			zone1_Coords.Y++;
			SetConsoleCursorPosition(h, zone1_Coords);
		}
	}
}

void scene::plrgen() const
{
	COORD zone1_Coords = { 7, 2 };
	SetConsoleCursorPosition(h, zone1_Coords);

	std::cout << "\033[1;35mP\033[0m";
}

void scene::plrupdate() const
{
	COORD zone1_Coords = { (playerpos.getx()*4)+3, playerpos.gety()+1 };
	SetConsoleCursorPosition(h, zone1_Coords);
	std::cout << "\033[1;35mP\033[0m" << "";
	COORD zone12_Coords = { 700, 2 };
	SetConsoleCursorPosition(h, zone12_Coords);
}