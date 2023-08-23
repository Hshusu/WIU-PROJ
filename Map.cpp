#include "Map.h"

void Map::Move(const int x, const int y) {
	if ((mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '.' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '|' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '-' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '_' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'X' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '+' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'R' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'A' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'L' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'Y' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '2' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '0' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '3' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '_' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'I' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'B' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '/' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '\\' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'S' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '^' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'C'
		)
	{
		Player_Pos.Y = (Player_Pos.Y + y);
		if (Player_Pos.Y < 0) {
			Player_Pos.Y = 0;
		}
		if (Player_Pos.Y > H - 1) {
			Player_Pos.Y = (H - 1);
		}
		Player_Pos.X = (Player_Pos.X + x);
		if (Player_Pos.X < 0) {
			Player_Pos.X = 0;
		}
		if (Player_Pos.X > W - 1) {
			Player_Pos.X = W - 1;
		}
	}
}

void Map::GenerateGrid()const
{
	//std::cout << "X: " << Player_Pos.X << "Y: " << Player_Pos.Y << std::end
	COORD GridCoords = { max_Size.X / 4 - (Player_Pos.X * 3), max_Size.Y / 4 - Player_Pos.Y };
	SetConsoleCursorPosition(outputHandle, GridCoords);
	for (int col = 0; col < H; col++)
	{
		for (int row = 0; row < W; row++)
		{
			SetConsoleTextAttribute(outputHandle, 3);
			if ((col == Player_Pos.Y) && (row == Player_Pos.X)) {
				std::cout << "P" << "  ";
			}
			else if (((col - Player_Pos.Y + (40 / 2)) > 10) && ((row - Player_Pos.X + (138 / 2)) > 60) && ((col - Player_Pos.Y + (40 / 2)) < 30) && ((row - Player_Pos.X + (138 / 2)) < 78)) {

				switch (mapVector[col][row]) {
				case '#':
					SetConsoleTextAttribute(outputHandle, 1);
					std::cout << mapVector[col][row] << "  ";
					break;
				case '.':
					SetConsoleTextAttribute(outputHandle, 2);
					std::cout << mapVector[col][row] << "  ";
					break;
				case 'D':
					SetConsoleTextAttribute(outputHandle, 4);
					std::cout << mapVector[col][row] << "  ";
					break;
				case 'C':
					SetConsoleTextAttribute(outputHandle, 4);
					std::cout << mapVector[col][row] << "  ";
					break;
				case 'X':
					SetConsoleTextAttribute(outputHandle, 2);
					std::cout << mapVector[col][row] << "  ";
					break;
				default:
					SetConsoleTextAttribute(outputHandle, 7);
					std::cout << mapVector[col][row] << "  ";
					break;
				}
			}
			else {
				std::cout << "   ";
			}
		}

		GridCoords.Y++;
		SetConsoleCursorPosition(outputHandle, GridCoords);
	}
}

void Map::UpdatePlayer() const
{
	Utility::PositionText(max_Size.X / 7, max_Size.Y / 2);
	std::cout << Cyan << "P" << ResetColour;
	Utility::PositionText(0, 0);
}

int Map::getCurrentDoor(void) const
{
	return currentDoor;
}

bool Map::checkObject(std::string Type)
{
	if (Type == "DOOR")
	{
		if ((mapVector[Player_Pos.Y + 1][Player_Pos.X]) == 'D'
			|| (mapVector[Player_Pos.Y][Player_Pos.X] + 1) == 'D'
			|| (mapVector[Player_Pos.Y - 1][Player_Pos.X]) == 'D'
			|| (mapVector[Player_Pos.Y][Player_Pos.X - 1]) == 'D')
		{
			//WORLD
			if (Player_Pos.X == 16 && Player_Pos.Y == 25)
			{
				currentDoor = WORLD_DETECTIVE_ROOM;
			}
			else if (Player_Pos.X == 18 && Player_Pos.Y == 13)
			{
				currentDoor = WORLD_LIBRARY;
			}
			else if (Player_Pos.X == 7 && Player_Pos.Y == 25)
			{
				currentDoor = WORLD_SHOP;
			}
			else if (Player_Pos.X == 3 && Player_Pos.Y == 30)
			{
				currentDoor = WORLD_STR;
			}
			else if (Player_Pos.X == 19 && Player_Pos.Y == 30)
			{
				currentDoor = WORLD_LUK;
			}

			//BACKDOORS
			if (Player_Pos.X == 3 && Player_Pos.Y == 13 ||
				Player_Pos.X == 5 && Player_Pos.Y == 13 ||
				Player_Pos.X == 2 && Player_Pos.Y == 5)
			{
				currentDoor = WORLD;
			}

			//LIBRARY
			if (Player_Pos.X == 1 && Player_Pos.Y == 13)
			{
				currentDoor = WORLD_LIBRARY;
			}

			//LIBRARYFORBIDDEN
			if (Player_Pos.X == 9 && Player_Pos.Y == 2)
			{
				currentDoor = LIBRARYFORBIDDEN;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (Type == "CLUE")
	{
		if ((mapVector[Player_Pos.Y][Player_Pos.X]) == 'C')
		{
			mapVector[Player_Pos.Y][Player_Pos.X] = '/';
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Map::checkNPC() const
{
	if ((mapVector[Player_Pos.Y + 1][Player_Pos.X]) == 'O'
		|| (mapVector[Player_Pos.Y][Player_Pos.X] + 1) == 'O'
		|| (mapVector[Player_Pos.Y - 1][Player_Pos.X]) == 'O'
		|| (mapVector[Player_Pos.Y][Player_Pos.X - 1]) == 'O')
	{
		return true;
	}
	else
	{
		return false;
	}
}

Map::Map()
{
}

void Map::setMap(int mapID)
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CSBI);
	Screen.X = CSBI.srWindow.Right - CSBI.srWindow.Left + 1;
	Screen.Y = CSBI.srWindow.Bottom - CSBI.srWindow.Top + 1;

	switch (mapID)
	{
	case WORLD:
			mapVector = {
			{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
			{'#','.','.','.','.','.','.','.','.','.','|','.','.','.','|','.','.','.','.','.','.','#',},
			{'#','.','-','-','-','-','-','-','-','\\','|','.','|','.','|','.','.','_','_','_','_','#',},
			{'#','/','.','.','.','.','.','.','.','|','|','.','|','.','|','X','X','|','.','.','.','#',},
			{'#','|','R','A','L','L','Y','.','C','|','|','.','|','.','|','X','X','|','[','=',']','#',},
			{'#','|','.','.','.','.','.','.','.','|','|','.','.','.','|','X','X','|','[','=',']','#',},
			{'#','|','.','.','.','2','0','2','3','|','|','.','.','.','|','.','.','|','^','_','_','#',},
			{'#','\\','-','-','-','-','-','-','-','/','|','.','.','.','|','.','.','/','L','\\','.','#',},
			{'#','.','.','.','.','.','.','.','.','.','|','.','|','.','|','.','.','-','-','-','.','#',},
			{'#','.','+','.','+','.','+','.','+','.','|','.','|','.','|','X','X','|','_','|','.','#',},
			{'#','.','.','.','.','.','.','.','.','.','|','.','|','.','|','X','X','|','0','|','.','#',},
			{'#','.','+','C','+','.','+','.','+','.','|','.','.','.','|','X','X','|','_','|','.','#',},
			{'#','.','.','.','.','.','.','.','.','.','|','.','.','.','|','X','X','_','D','_','.','#',},
			{'#','.','+','.','+','.','+','.','+','.','|','.','.','.','|','.','.','.','.','.','.','#',},
			{'#','_','_','_','_','_','_','_','_','_','_','.','|','.','_','_','_','_','_','_','_','#',},
			{'#','.','.','.','.','.','.','.','.','.','.','.','|','.','.','.','.','.','.','.','.','#',},
			{'#','-','-','.','-','-','-','.','-','-','-','.','|','.','-','-','-','.','-','-','-','#',},
			{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
			{'#','_','_','_','_','_','_','_','_','_','-','O','.','.','_','_','_','_','_','_','_','#',},
			{'#','.','.','.','.','.','.','.','.','.','|','.','.','.','|','.','.','.','.','.','.','#',},
			{'#','.','.','.','.','.','.','^','.','.','|','.','|','.','|','.','^','.','.','X','X','#',},
			{'#','.','X','X','X','.','/','S','\\','.','|','.','|','.','|','/','R','\\','.','X','X','#',},
			{'#','.','X','X','X','.','_','_','_','.','|','.','|','.','|','_','_','_','.','X','X','#',},
			{'#','.','X','X','X','.','|','_','|','.','|','.','.','.','|','|','_','|','.','X','X','#',},
			{'#','.','.','.','.','.','_','D','_','.','|','.','.','.','|','_','D','_','.','.','.','#',},
			{'#','.','.','^','.','.','.','.','.','.','|','.','|','.','|','.','.','.','.','^','.','#',},
			{'#','.','/','0','\\','.','.','.','.','.','|','.','|','.','|','.','.','.','/','0','\\','#',},
			{'#','.','_','_','_','.','X','X','X','.','|','.','|','.','|','X','X','.','_','_','_','#',},
			{'#','.','|','_','|','.','X','X','X','.','|','.','.','.','|','X','X','.','|','_','|','#',},
			{'#','.','_','D','_','.','X','X','X','.','|','.','.','.','|','X','X','.','_','D','_','#',},
			{'#','.','.','.','.','.','.','.','.','.','|','.','.','.','|','.','.','.','.','.','.','#',},
			{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
		};
		break;
	case DETECTIVE_ROOM:
		mapVector = {
		{'#','#','#','#','#','#','#',},
		{'#','.','.','.','.','.','#',},
		{'#','-','.','.','.','.','#',},
		{'#','[','0','.','C','{','#',},
		{'#','[','0','.','.','.','#',},
		{'#','_','.','.','.','.','#',},
		{'#','.','.','.','.','{','#',},
		{'#','X','.','.','.','.','#',},
		{'#','X','.','.','.','.','#',},
		{'#','.','.','.','.','{','#',},
		{'#','-','.','.','.','.','#',},
		{'#','G','0','.','.','.','#',},
		{'#','[','0','.','.','{','#',},
		{'#','-','.','.','.','.','#',},
		{'#','.','.','D','.','.','#',},
		{'#','#','#','#','#','#','#',},
		};
		break;
	case LIBRARY:
		mapVector = {
		{'#','#','#','#','#','#','#','#','#','#','#',},
		{'#','.','.','+','-','-','-','+','.','D','#',},
		{'#','-','-','|','.','L','.','|','.','.','#',},
		{'#','[',']','+','-','-','-','+','.','.','#',},
		{'#','[',']','.','.','.','.','.','.','.','#',},
		{'#','_','_','C','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','D','.','.','.','.','#',},
		{'#','#','#','#','#','#','#','#','#','#','#',},
		};
		break;
	case LIBRARY_FORBIDDEN:
		mapVector = {
		{'#','#','#','#','#','#','#','#','#','#','#',},
		{'#','[','=','=','=','?','=','=','=',']','#',},
		{'#','.','C','.','.','.','.','.','.','.','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','D','.','.','.','.','.','.','.','C','#',},
		{'#','#','#','#','#','#','#','#','#','#','#',},
		};
		break;
	case SHOP:
		mapVector = {
		{'#','#','#','#','#','#','#','#','#','#','#',},
		{'#','.','.','+','-','-','-','+','.','.','#',},
		{'#','-','.','|','.','S','.','|','.','-','#',},
		{'#','[','C','+','-','-','-','+','O',']','#',},
		{'#','[','.','O','.','.','.','.','.',']','#',},
		{'#','-','.','.','.','.','.','.','.','-','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','O','.','.','.','.','.','O','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','.','.','O','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','D','.','.','.','O','#',},
		{'#','#','#','#','#','#','#','#','#','#','#',},
		};
		break;
	case STRENGTH_HOUSE:
		mapVector = {
		{'#','#','#','#','#',},
		{'#','-','.','C','#',},
		{'#','[','0','>','#',},
		{'#','-','.','.','#',},
		{'#','S','.','D','#',},
		{'#','.','.','.','#',},
		{'#','.','D','.','#',},
		{'#','#','#','#','#',},
		};
		break;
	case LUCK_HOUSE:
		mapVector = {
		{'#','#','#','#','#',},
		{'#','-','.','C','#',},
		{'#','[','0','>','#',},
		{'#','-','.','.','#',},
		{'#','L','.','D','#',},
		{'#','.','.','.','#',},
		{'#','.','D','.','#',},
		{'#','#','#','#','#',},
		};
		break;
	}
	H = mapVector.size();
	W = mapVector[0].size();
	Player_Pos.Y = (H / 2);
	Player_Pos.X = (W / 2);
}