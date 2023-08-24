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
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'C' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'V' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'D' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == 'O' ||
		(mapVector[Player_Pos.Y + y][Player_Pos.X + x]) == ' '
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
			if (Utility::randomNumber(1, 100) == 17)
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

void Map::setDefeatedValeria(bool dV)
{
	defeatedValeria = dV;
}

void Map::setCoinBought(bool cB)
{
	CoinBought = cB;
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
		if ((mapVector[Player_Pos.Y][Player_Pos.X]) == 'D')
		{
			//WORLD
			if (Player_Pos.X == 16 && Player_Pos.Y == 24)
			{
				currentDoor = WORLD_DETECTIVE_ROOM;
				currentRoomText1 = " > You feel a sense of invigorating power as you step into the room. Pictures of Military High Rankers decorated the";
				currentRoomText2 = "   walls. On the couch sits General Blackthorn, awaiting your arrival.";
				currentRoomText3 = "";
			}
			else if (Player_Pos.X == 18 && Player_Pos.Y == 12 && talkedGeneral == true)
			{
				currentDoor = WORLD_LIBRARY;
				currentRoomText1 = " > You are enveloped by an air of knowledge and serenity. Rows upon rows of towering bookshelves appear in your view.";
				currentRoomText2 = "   Something, however, seems odd... The books are all... arranged wrongly..?";
				currentRoomText3 = "";
			}
			else if (Player_Pos.X == 7 && Player_Pos.Y == 24 && talkedTomekeeper == true)
			{
				currentDoor = WORLD_SHOP;
				currentRoomText1 = " > Gleaming crystals, shimmering amulets, and spellbound trinkets adorn the shelves, each item resonating with arcane";
				currentRoomText2 = "   energy. The air is scented with an intoxicating blend of herbs and enchantments, inviting you to explore the";
				currentRoomText3 = "   within.";
			}
			else if (Player_Pos.X == 3 && Player_Pos.Y == 29 && talkedAurelius == true)
			{
				currentDoor = WORLD_STR;
				currentRoomText1 = " > As you step into this imposing domain, the air itself seems to hum with power. The walls are adorned with trophies";
				currentRoomText2 = "   of battles long won, of battles long won, and the floors bear the marks of training and conquest.";
				currentRoomText3 = "";
			}
			else if (Player_Pos.X == 19 && Player_Pos.Y == 29 && talkedValeria == true)
			{
				currentDoor = WORLD_LUK;
				currentRoomText1 = " > The walls are adorned with symbols of good fortune and prosperity, and the atmosphere is alive with an almost";
				currentRoomText2 = "   tangible sense of luck. The stars themselves seem to align in your favor, making every moment feel like a stroke of serendipity.";
				currentRoomText3 = " ";
			}
			else
			{
				currentRoomText1 = " > The door seems to be locked. Perhaps I should do something else first.";
				currentRoomText2 = "";
				currentRoomText3 = "";
			}

			//BACKDOORS
			if (Player_Pos.X == 3 && Player_Pos.Y == 14 ||
				Player_Pos.X == 5 && Player_Pos.Y == 14 ||
				Player_Pos.X == 2 && Player_Pos.Y == 6)
			{
				currentDoor = WORLD;
				currentRoomText1 = "";
				currentRoomText2 = "";
				currentRoomText3 = "";
			}

			//LIBRARY
			if (Player_Pos.X == 1 && Player_Pos.Y == 12)
			{
				currentDoor = WORLD_LIBRARY;
				currentRoomText1 = " > You are enveloped by an air of knowledge and serenity. Rows upon rows of towering bookshelves appear in your view.";
				currentRoomText2 = "   Something, however, seems odd... The books are all... arranged wrongly..?";
				currentRoomText3 = "";
			}

			//LIBRARYFORBIDDEN
			if (Player_Pos.X == 9 && Player_Pos.Y == 1 && currentStamps == 3)
			{
				currentDoor = LIBRARYFORBIDDEN;
				currentRoomText1 = " > A palpable sense of foreboding washes over you, the air is thick with an aura of enigma and trepidation. The";
				currentRoomText2 = "   whispers of forbidden spells and malevolent incantations seem to linger, a haunting reminder of the mysteries";
				currentRoomText3 = "   concealed within.";
			}
			else if (Player_Pos.X == 9 && Player_Pos.Y == 1 && currentStamps != 3)
			{
				currentRoomText1 = " > This area of the Archive is currently enclouded with some kind of Magical Barrier.";
				currentRoomText2 = "";
				currentRoomText3 = "";
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
	/*if ((mapVector[Player_Pos.Y + 1][Player_Pos.X]) == 'O'
		|| (mapVector[Player_Pos.Y][Player_Pos.X] + 1) == 'O'
		|| (mapVector[Player_Pos.Y - 1][Player_Pos.X]) == 'O'
		|| (mapVector[Player_Pos.Y][Player_Pos.X - 1]) == 'O')
	{
		return true;
	}
	else
	{
		return false;
	}*/
	if ((mapVector[Player_Pos.Y][Player_Pos.X]) == 'O')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Map::checkSpecialNPC(std::string& DialogueNPC, std::string& QuestionsFileStr, std::string& ResponsesFileStr, bool& combatEnabled, int& enemyID, int& State, bool& hostilityEnabled)
{
	if ((mapVector[Player_Pos.Y][Player_Pos.X]) == 'G' ||
		(mapVector[Player_Pos.Y][Player_Pos.X]) == 'I' ||
		(mapVector[Player_Pos.Y][Player_Pos.X]) == 'S' ||
		(mapVector[Player_Pos.Y][Player_Pos.X]) == 'V')
	{
		if (Player_Pos.X == 1 && Player_Pos.Y == 11)
		{
			hostilityEnabled = true;
			currentSpecialNPC = GENERAL_BLACKTHORN;
			DialogueNPC = "Arcadia's Chief General | General Blackthorn [HUMAN]";
			QuestionsFileStr = "General Blackthorn Questions.txt";
			ResponsesFileStr = "General Blackthorn Responses.txt";
			talkedGeneral = true;
			State = DIALOGUE;
		}
		else if (Player_Pos.X == 5 && Player_Pos.Y == 2 && mapVector[Player_Pos.Y][Player_Pos.X] == 'I')
		{
			hostilityEnabled = true;
			currentSpecialNPC = ISABELLA_NIGHTSHADE;
			DialogueNPC = "Arcadia's Tomekeeper | Isabella Nightshade [HUMAN]";
			QuestionsFileStr = "Isabella Nightshade Questions.txt";
			ResponsesFileStr = "Isabella Nightshade Responses.txt";
			talkedTomekeeper = true;
			State = DIALOGUE;
		}
		else if (Player_Pos.X == 5 && Player_Pos.Y == 2 && mapVector[Player_Pos.Y][Player_Pos.X] == 'S')
		{
			currentSpecialNPC = AURELIUS_MINDWEAVER;
			DialogueNPC = "Arcadia's Shopkeeper | Kranny Schrodinger [ELF]";

			if (defeatedAurelius == false)
			{
				if (talkedAurelius == false)
				{
					hostilityEnabled = false;
					QuestionsFileStr = "Aurelius Mindweaver 1 Questions.txt";
					ResponsesFileStr = "Aurelius Mindweaver 1 Responses.txt";
					talkedAurelius = true;
					State = DIALOGUE;
				}
				else
				{
					State = STORE;
				}
			}
			else
			{
				hostilityEnabled = false;
				DialogueNPC = "Arcadia's Wise Sage | Aurelius Mindweaver [ELF]";
				QuestionsFileStr = "Aurelius Mindweaver 2 Questions.txt";
				ResponsesFileStr = "Aurelius Mindweaver 2 Responses.txt";
				currentStamps++;
			}
		}
		else if (Player_Pos.X == 1 && Player_Pos.Y == 4 && mapVector[Player_Pos.Y][Player_Pos.X] == 'V')
		{
			currentSpecialNPC = VALERIA_STORMBRINGER;
			DialogueNPC = "Arcadia's Mighty Warden | Valeria Stormbringer [ORC]";
			if (defeatedValeria == false)
			{
				hostilityEnabled = true;
				QuestionsFileStr = "Valeria Stormbringer 1 Questions.txt";
				ResponsesFileStr = "Valeria Stormbringer 1 Responses.txt";
				combatEnabled = true;
				enemyID = 0;
			}
			else
			{
				hostilityEnabled = false;
				combatEnabled = false;
				QuestionsFileStr = "Valeria Stormbringer 2 Questions.txt";
				ResponsesFileStr = "Valeria Stormbringer 2 Responses.txt";
				currentStamps++;
				talkedValeria = true;
			}
			State = DIALOGUE;
		}
		else if (Player_Pos.X == 1 && Player_Pos.Y == 4 && mapVector[Player_Pos.Y][Player_Pos.X] == 'S')
		{
			currentSpecialNPC = SERAPHINA_FORTUNA;
			DialogueNPC = "Arcadia's Fortune Teller | Seraphina Fortuna [HUMAN]";

			if (seraphinaCoinPuzzle == false)
			{
				if (defeatedSeraphina == false)
				{
					hostilityEnabled = false;
					QuestionsFileStr = "Seraphina Fortuna 1 Questions.txt";
					ResponsesFileStr = "Seraphina Fortuna 1 Responses.txt";
					seraphinaCoinPuzzle = true;
				}
				else
				{
					hostilityEnabled = false;
					QuestionsFileStr = "Seraphina Fortuna 2 Questions.txt";
					ResponsesFileStr = "Seraphina Fortuna 2 Responses.txt";
					defeatedAurelius = true;
					currentStamps++;
				}
			}
			else
			{
				Utility::PositionText(0, 28);
				Utility::typewriterText(" > You approach Seraphina and present a Coin. With a deep breath, she takes the Coin and places it on her", 10);
				Utility::PositionText(0, 29);
				Utility::typewriterText("   thumb. She flicks it gracefully up in the air, and slammed the Coin down into her palms as it came", 10);
				Utility::PositionText(0, 30);
				Utility::typewriterText("   falling back down. She slowly reveals her hand... and the results are...", 10);

				if (CoinBought == true)
				{
					Utility::PositionText(0, 32);
					Utility::typewriterText(" > The Coin favours you, you won!", 10);
					defeatedSeraphina = true;
				}
				else
				{
					Utility::PositionText(0, 32);
					Utility::typewriterText(" > The Coin favours Seraphina, you lost!", 10);
					defeatedSeraphina = false;
				}

			}
			State = DIALOGUE;
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
			{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
			{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ',' ',' ',' ','#',},
			{'#','/','-','-','-','-','-','-','-','\\','|',' ','|','.','|',' ',' ','_','_','_','_','#',},
			{'#','|',' ','R','A','L','L','Y',' ','|','|',' ','^',' ','|','X','X','|',' ',' ',' ','#',},
			{'#','|',' ','S','T','A','G','E',' ','|','|',' ','|',' ','|','X','X','|','[','=',']','#',},
			{'#','|',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ','|','X','X','|','[','=',']','#',},
			{'#','|',' ',' ',' ','C',' ',' ',' ','|','|',' ',' ',' ','|',' ',' ','|','_','_','_','#',},
			{'#','\\','-','-','-','-','-','-','-','/','|',' ',' ',' ','|',' ',' ','|','L','|',' ','#',},
			{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','|',' ','|',' ',' ','-','-','-',' ','#',},
			{'#',' ','+',' ','+',' ','+',' ','+',' ','|',' ','^',' ','|','X','X','|','_','|',' ','#',},
			{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','|',' ','|','X','X','|','0','|',' ','#',},
			{'#',' ','+',' ','+',' ','+',' ','+',' ','|',' ',' ',' ','|','X','X','|','_','|',' ','#',},
			{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|','X','X','_','D','_',' ','#',},
			{'#',' ','+',' ','+',' ','+',' ','+',' ','|',' ',' ',' ','|',' ',' ',' ',' ',' ',' ','#',},
			{'#','-','-','-','-','-','-','-','-','-','-',' ','|',' ','-','-','-','-','-','-','-','#',},
			{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','^',' ',' ',' ',' ',' ',' ',' ',' ','#',},
			{'#','<','-',' ','-','<','-',' ','<','-','-',' ','|',' ','-','<','-',' ','-','<','-','#',},
			{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
			{'#','-','-','-','-','-','-','-','-','-','-',' ',' ',' ','-','-','-','-','-','-','-','#',},
			{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ',' ',' ',' ','#',},
			{'#',' ','X','X','X',' ',' ','^',' ',' ','|',' ','|',' ','|',' ','^',' ',' ','X','X','#',},
			{'#',' ','X','X','X',' ','/','S','\\',' ','|',' ','^',' ','|','/','R','\\',' ','X','X','#',},
			{'#',' ','X','X','X',' ','_','_','_',' ','|',' ','|',' ','|','_','_','_',' ','X','X','#',},
			{'#',' ','X','X','X',' ','|','_','|',' ','|',' ',' ',' ','|','|','_','|',' ','X','X','#',},
			{'#',' ',' ',' ',' ',' ','_','D','_',' ','|',' ',' ',' ','|','_','D','_',' ',' ',' ','#',},
			{'#',' ',' ','^',' ',' ',' ',' ',' ',' ','|',' ','|',' ','|',' ',' ',' ',' ','^',' ','#',},
			{'#',' ','/','0','\\',' ',' ',' ',' ',' ','|',' ','^',' ','|',' ',' ',' ','/','0','\\','#',},
			{'#',' ','_','_','_',' ','X','X','X',' ','|',' ','|',' ','|','X','X',' ','_','_','_','#',},
			{'#',' ','|','_','|',' ','X','X','X',' ','|',' ',' ',' ','|','X','X',' ','|','_','|','#',},
			{'#',' ','_','D','_',' ',' ',' ',' ',' ','|',' ','|',' ','|','X','X',' ','_','D','_','#',},
			{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','^',' ','|',' ',' ',' ',' ',' ',' ','#',},
			{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
		};
		break;
	case DETECTIVE_ROOM:
		mapVector = {
		{'#','#','#','#','#','#','#',},
		{'#',' ',' ',' ',' ',' ','#',},
		{'#','-',' ',' ',' ',' ','#',},
		{'#','[','0',' ',' ','{','#',},
		{'#','[','0',' ',' ',' ','#',},
		{'#','_',' ',' ',' ',' ','#',},
		{'#',' ',' ',' ',' ',' ','#',},
		{'#','X',' ',' ',' ',' ','#',},
		{'#','X',' ',' ',' ',' ','#',},
		{'#',' ',' ',' ',' ','{','#',},
		{'#','-',' ',' ',' ',' ','#',},
		{'#','G','0',' ',' ',' ','#',},
		{'#','[','0',' ',' ','{','#',},
		{'#','-',' ',' ',' ',' ','#',},
		{'#',' ',' ','D',' ',' ','#',},
		{'#','#','#','#','#','#','#',},
		};
		break;
	case LIBRARY:
		mapVector = {
		{'#','#','#','#','#','#','#','#','#','#','#',},
		{'#',' ',' ','+','-','-','-','+',' ','D','#',},
		{'#','-','-','|','.','I','.','|',' ',' ','#',},
		{'#','[',']','+','-','-','-','+',' ',' ','#',},
		{'#','[',']',' ',' ',' ',' ',' ',' ',' ','#',},
		{'#','_','_','C',' ',' ',' ',' ',' ',' ','#',},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
		{'#',' ',' ',' ',' ',' ',' ',' ','C',' ','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
		{'#',' ',' ',' ',' ','D',' ',' ',' ',' ','#',},
		{'#','#','#','#','#','#','#','#','#','#','#',},
		};
		break;
	case LIBRARY_FORBIDDEN:
		mapVector = {
		{'#','#','#','#','#','#','#','#','#','#','#',},
		{'#','[','=','=','=','?','=','=','=',']','#',},
		{'#',' ',' ',' ',' ','C',' ',' ',' ',' ','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
		{'#','D',' ',' ',' ',' ',' ',' ',' ','C','#',},
		{'#','#','#','#','#','#','#','#','#','#','#',},
		};
		break;
	case SHOP:
		mapVector = {
		{'#','#','#','#','#','#','#','#','#','#','#',},
		{'#',' ',' ','+','-','-','-','+',' ',' ','#',},
		{'#','-',' ','|',' ','S',' ','|',' ','-','#',},
		{'#','[','C','+','-','-','-','+','O',']','#',},
		{'#','[',' ','O',' ',' ',' ',' ',' ',']','#',},
		{'#','-',' ',' ',' ',' ',' ',' ',' ','-','#',},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#','O',' ',' ',' ',' ',' ','O',' ',' ','#',},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#','[','=','=',']',' ','[','=','=',']','#',},
		{'#',' ',' ','O',' ',' ',' ',' ',' ',' ','#',},
		{'#',' ',' ',' ',' ','D',' ',' ',' ','O','#',},
		{'#','#','#','#','#','#','#','#','#','#','#',},
		};
		break;
	case STRENGTH_HOUSE:
		mapVector = {
		{'#','#','#','#','#',},
		{'#','-',' ',' ','#',},
		{'#','[','0','>','#',},
		{'#','-',' ',' ','#',},
		{'#','V',' ',' ','#',},
		{'#',' ',' ',' ','#',},
		{'#',' ','D',' ','#',},
		{'#','#','#','#','#',},
		};
		break;
	case LUCK_HOUSE:
		mapVector = {
		{'#','#','#','#','#',},
		{'#','-',' ',' ','#',},
		{'#','[','0','>','#',},
		{'#','-',' ',' ','#',},
		{'#','S',' ',' ','#',},
		{'#',' ',' ',' ','#',},
		{'#',' ','D',' ','#',},
		{'#','#','#','#','#',},
		};
		break;
	}
	H = mapVector.size();
	W = mapVector[0].size();
	Player_Pos.Y = (H / 2);
	Player_Pos.X = (W / 2);
}