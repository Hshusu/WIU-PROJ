#include "Map.h"

void Map::Move(const int x, const int y, int &State, int &enemyID) {
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
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == '<' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'S' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'T' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'G' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'E' ||
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

		if ((mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'X')
		{
			if (Utility::randomNumber(1, 2) == 1)
			{
				State = 6;
				enemyID = Utility::randomNumber(0, 3);
			}
		}
	}
}

void Map::GenerateGrid()const
{
	Utility::PositionText(15, 20);
	std::cout << "X: " << Player_Pos.X << "Y: " << Player_Pos.Y << std::endl;
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

std::string Map::getCurrentRoomText1(void) const
{
	return currentRoomText1;
}

std::string Map::getCurrentRoomText2(void) const
{
	return currentRoomText2;
}

std::string Map::getCurrentRoomText3(void) const
{
	return currentRoomText3;
}

int Map::getCurrentClue(void) const
{
	return currentClue;
}

int Map::getCurrentDoor(void) const
{
	return currentDoor;
}

int Map::getCurrentSpecialNPC(void) const
{
	return currentSpecialNPC;
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
			if (Player_Pos.X == 17 && Player_Pos.Y == 25)
			{
				currentDoor = WORLD_DETECTIVE_ROOM;
				currentRoomText1 = " > You feel a sense of invigorating power as you step into the room.";
				currentRoomText2 = "   Pictures of Military High Rankers decorated the walls.";
				currentRoomText3 = "   On the couch sits General Blackthorn, awaiting your arrival.";
			}
			else if (Player_Pos.X == 19 && Player_Pos.Y == 13)
			{
				currentDoor = WORLD_LIBRARY;
				currentRoomText1 = " > You are enveloped by an air of knowledge and serenity.";
				currentRoomText2 = "   Rows upon rows of towering bookshelves appear in your view.";
				currentRoomText3 = "   Something, however, seems odd... The books are all... arranged wrongly..?";
			}
			else if (Player_Pos.X == 8 && Player_Pos.Y == 25)
			{
				currentDoor = WORLD_SHOP;
				currentRoomText1 = " > Gleaming crystals, shimmering amulets, and spellbound trinkets adorn the shelves,";
				currentRoomText2 = "   each item resonating with arcane energy. The air is scented with an intoxicating blend of herbs and enchantments,";
				currentRoomText3 = "   inviting you to explore the secrets within.";
			}
			else if (Player_Pos.X == 4 && Player_Pos.Y == 30)
			{
				currentDoor = WORLD_STR;
				currentRoomText1 = " > As you step into this imposing domain, the air itself seems to hum with power.";
				currentRoomText2 = "   The walls are adorned with trophies of battles long won,";
				currentRoomText3 = "   and the floors bear the marks of training and conquest.";
			}
			else if (Player_Pos.X == 20 && Player_Pos.Y == 30)
			{
				currentDoor = WORLD_LUK;
				currentRoomText1 = " > The walls are adorned with symbols of good fortune and prosperity,";
				currentRoomText2 = "   and the atmosphere is alive with an almost tangible sense of luck.";
				currentRoomText3 = "   The stars themselves seem to align in your favor, making every moment feel like a stroke of serendipity.";
			}

			//BACKDOORS
			if (Player_Pos.X == 3 && Player_Pos.Y == 13 ||
				Player_Pos.X == 5 && Player_Pos.Y == 13 ||
				Player_Pos.X == 2 && Player_Pos.Y == 5)
			{
				currentDoor = WORLD;
				currentRoomText1 = "";
				currentRoomText2 = "";
				currentRoomText3 = "";
			}

			//LIBRARY
			if (Player_Pos.X == 1 && Player_Pos.Y == 13)
			{
				currentDoor = WORLD_LIBRARY;
				currentRoomText1 = " > You are enveloped by an air of knowledge and serenity.";
				currentRoomText2 = "   Rows upon rows of towering bookshelves appear in your view.";
				currentRoomText3 = "   Something, however, seems odd... The books are all... arranged wrongly..?";
			}

			//LIBRARYFORBIDDEN
			if (Player_Pos.X == 9 && Player_Pos.Y == 2)
			{
				currentDoor = LIBRARYFORBIDDEN;
				currentRoomText1 = " > A palpable sense of foreboding washes over you, the air is thick with an aura of enigma and trepidation.";
				currentRoomText2 = "   The whispers of forbidden spells and malevolent incantations seem to linger,";
				currentRoomText3 = "   a haunting reminder of the mysteries concealed within.";
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
			mapVector[Player_Pos.Y][Player_Pos.X] = '@';

			if (Player_Pos.X == 3 && Player_Pos.Y == 5)
			{
				currentClue = DEAD_BODY;
			}
			else if (Player_Pos.X == 4 && Player_Pos.Y == 3)
			{
				currentClue = WAR_HERO_PHOTO;
			}
			else if (Player_Pos.X == 8 && Player_Pos.Y == 10)
			{
				currentClue = MESSY_BOOKS;
			}
			else if (Player_Pos.X == 3 && Player_Pos.Y == 5)
			{
				currentClue = NEWSPAPERS;
			}
			else if (Player_Pos.X == 2 && Player_Pos.Y == 3)
			{
				currentClue = COIN;
			}
			else if (Player_Pos.X == 5 && Player_Pos.Y == 2)
			{
				currentClue = MISSING_PAGES;
			}
			else if (Player_Pos.X == 9 && Player_Pos.Y == 14)
			{
				currentClue = SNAKE_SKIN;
			}

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

bool Map::checkSpecialNPC(std::string& DialogueNPC, std::string& QuestionsFileStr, std::string& ResponsesFileStr)
{
	if ((mapVector[Player_Pos.Y][Player_Pos.X]) == 'G' ||
		(mapVector[Player_Pos.Y][Player_Pos.X]) == 'I' ||
		(mapVector[Player_Pos.Y][Player_Pos.X]) == 'S' ||
		(mapVector[Player_Pos.Y][Player_Pos.X]) == 'V')
	{
		if (Player_Pos.X == 1 && Player_Pos.Y == 11)
		{
			currentSpecialNPC = GENERAL_BLACKTHORN;
			DialogueNPC = "[Arcadia's Chief General] General Blackthorn";
			QuestionsFileStr = "";
			ResponsesFileStr = "";
		}
		else if (Player_Pos.X == 5 && Player_Pos.Y == 2 && mapVector[Player_Pos.Y][Player_Pos.X] == 'I')
		{
			currentClue = ISABELLA_NIGHTSHADE;
		}
		else if (Player_Pos.X == 5 && Player_Pos.Y == 2 && mapVector[Player_Pos.Y][Player_Pos.X] == 'S')
		{
			currentClue = AURELIUS_MINDWEAVER;
		}
		else if (Player_Pos.X == 1 && Player_Pos.Y == 4 && mapVector[Player_Pos.Y][Player_Pos.X] == 'V')
		{
			currentClue = VALERIA_STORMBRINGER;
		}
		else if (Player_Pos.X == 1 && Player_Pos.Y == 4 && mapVector[Player_Pos.Y][Player_Pos.X] == 'S')
		{
			currentClue = SERAPHINA_FORTUNA;
		}

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
			{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
			{'#','.','.','.','.','.','.','.','.','.','.','|','.','.','.','|','.','.','.','.','.','.','#',},
			{'#','/','-','-','-','-','-','-','-','-','\\','|','.','|','.','|','.','.','_','_','_','_','#',},
			{'#','|','R','A','L','L','Y','.','.','.','|','|','.','^','.','|','X','X','|','.','.','.','#',},
			{'#','|','.','.','S','T','A','G','E','.','|','|','.','|','.','|','X','X','|','[','=',']','#',},
			{'#','|','.','C','.','.','2','0','2','3','|','|','.','.','.','|','X','X','|','[','=',']','#',},
			{'#','|','.','.','.','.','.','.','.','.','|','|','.','.','.','|','.','.','|','_','_','_','#',},
			{'#','\\','-','-','-','-','-','-','-','-','/','|','.','.','.','|','.','.','/','L','\\','.','#',},
			{'#','.','.','.','.','.','.','.','.','.','.','|','.','|','.','|','.','.','-','-','-','.','#',},
			{'#','+','.','+','.','+','.','+','.','+','.','|','.','^','.','|','X','X','|','_','|','.','#',},
			{'#','.','.','.','.','.','.','.','.','.','.','|','.','|','.','|','X','X','|','0','|','.','#',},
			{'#','+','.','+','.','+','.','+','.','+','.','|','.','.','.','|','X','X','|','_','|','.','#',},
			{'#','.','.','.','.','.','.','.','.','.','.','|','.','.','.','|','X','X','_','D','_','.','#',},
			{'#','+','.','+','.','+','.','+','.','+','.','|','.','.','.','|','.','.','.','.','.','.','#',},
			{'#','-','-','-','-','-','-','-','-','-','-','-','.','|','.','-','-','-','-','-','-','-','#',},
			{'#','.','.','.','.','.','.','.','.','.','.','.','.','^','.','.','.','.','.','.','.','.','#',},
			{'#','-','<','-','.','-','<','-','.','<','-','-','.','|','.','-','<','-','.','-','<','-','#',},
			{'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#',},
			{'#','-','-','-','-','-','-','-','-','-','-','-','O','.','.','-','-','-','-','-','-','-','#',},
			{'#','.','.','.','.','.','.','.','.','.','.','|','.','.','.','|','.','.','.','.','.','.','#',},
			{'#','X','X','.','X','X','.','.','^','.','.','|','.','|','.','|','.','^','.','.','X','X','#',},
			{'#','X','X','.','X','X','.','/','S','\\','.','|','.','^','.','|','/','R','\\','.','X','X','#',},
			{'#','X','X','.','X','X','.','_','_','_','.','|','.','|','.','|','_','_','_','.','X','X','#',},
			{'#','X','X','.','X','X','.','|','_','|','.','|','.','.','.','|','|','_','|','.','X','X','#',},
			{'#','.','.','.','.','.','.','_','D','_','.','|','.','.','.','|','_','D','_','.','.','.','#',},
			{'#','.','.','.','^','.','.','.','.','.','.','|','.','|','.','|','.','.','.','.','^','.','#',},
			{'#','X','X','/','0','\\','.','.','.','.','.','|','.','^','.','|','.','.','.','/','0','\\','#',},
			{'#','X','X','_','_','_','.','X','X','X','.','|','.','|','.','|','X','X','.','_','_','_','#',},
			{'#','X','X','|','_','|','.','X','X','X','.','|','.','.','.','|','X','X','.','|','_','|','#',},
			{'#','X','X','_','D','_','.','X','X','X','.','|','.','|','.','|','X','X','.','_','D','_','#',},
			{'#','.','.','.','.','.','.','.','.','.','.','|','.','^','.','|','.','.','.','.','.','.','#',},
			{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
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
		{'#','-','-','|','.','I','.','|','.','.','#',},
		{'#','[',']','+','-','-','-','+','.','.','#',},
		{'#','[',']','.','.','.','.','.','.','.','#',},
		{'#','_','_','C','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','[','=','=',']','.','[','=','=',']','#',},
		{'#','.','.','.','.','.','.','.','.','.','#',},
		{'#','.','.','.','.','.','.','.','C','.','#',},
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
		{'#','.','.','.','.','C','.','.','.','.','#',},
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
		{'#','-','.','.','#',},
		{'#','[','0','>','#',},
		{'#','-','.','.','#',},
		{'#','V','.','.','#',},
		{'#','.','.','.','#',},
		{'#','.','D','.','#',},
		{'#','#','#','#','#',},
		};
		break;
	case LUCK_HOUSE:
		mapVector = {
		{'#','#','#','#','#',},
		{'#','-','.','.','#',},
		{'#','[','0','>','#',},
		{'#','-','.','.','#',},
		{'#','S','.','.','#',},
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