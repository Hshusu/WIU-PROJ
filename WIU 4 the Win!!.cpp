#include <iostream>
#include <random>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <cwchar>
#include <WinUser.h>

#include "Utility.h"

#include "Player.h"
#include "Main_character.h"
//Exploration
#include "Map.h"

//Combat
#include "Entity.h"
#include "Npc.h"
#include"Item.h"
#include"inventory.h"
//Dialogue
#include "Dialogue.h"

//Events
#include "Equipment.h"

//Puzzles
#include "CluePuzzle.h"
#include "Clue.h"
#include "ConclusiveClue.h"
#include "SpecialNPC.h"


#pragma comment(lib, "Winmm.lib")

enum StateNames
{
	//Main
	EXPLORATION,
	WEAPON,
	INVENTORY,
	CUTSCENE,
	//Events
	LEVELUP,
	DIALOGUE,
	//Actions
	COMBAT,
	ITEM,
	//Exit
	EXIT,
	RESET,
};

bool crParty(Player* player[4]) {
	for (int i = 0; i < 4; i++) {
		if (player[i] != nullptr) {

			if (player[i]->CheckCR())
			{
				return true;

			}
		}
	}
	return false;
}

int main()
{
	std::cout << "Playing Music" << std::endl;

	PlaySound(TEXT("Test.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	//std::string input;
	//std::getline(std::cin, input);
	//PlaySound(0, 0, 0);
	//std::cout << "Stopped Music" << std::endl;

	int States = EXPLORATION;

	//General
	COORD Screen;
	Utility::MaxScreen();

	//Exploration
	bool map_Loaded = false;
	bool text_Loaded = false;
	Map newMap;

	//Dialogue
	std::string DialogueNPC, QuestionsFileStr, ResponsesFileStr;

	//Combat
	const int max_Party_size = 4;
	float PMods[6] = { 1,1,1,1,1,1 };
	int enemyID = 2;
	Player* Plr[max_Party_size] = { nullptr };
	Plr[0] = new Main_character(PMods, "Aurelius Mindweaver", Lightning, Ice);
	Plr[1] = new Player("Seraphina Fortuna", 1.1, 10, 2, 20, Fire, Darkness);
	NPC* Placeholder_Enemy[10] = { nullptr };
	Placeholder_Enemy[0] = new NPC("placeholder", 2, 10, 1.5, 20, Fire, Darkness);
	Placeholder_Enemy[1] = new NPC("kk", 2, 10, 1.5, 20, Fire, Darkness);
	Placeholder_Enemy[2] = new NPC("hshusu", 2, 10, 1.5, 20, Fire, Darkness);
	Placeholder_Enemy[3] = new NPC("blade", 2, 10, 1.5, 20, Fire, Darkness);

	//Clue
	//The Rally
	Clue deadBody("Cedric Everhart's body", "There seems to be strange markings in this seemly Bloodshot eyes...", ClueType::Physical);
	SpecialNPC Cedric_Everhart("Cedric Everhart", "I heard a loud noise and saw someone running away from the crime scene.");

	//Generals' Office
	Clue heroPhoto("War Hero", "A photo that shows Deceased Cedric Everhart standing next to General Blackthorn, holding a Medal representing the Peace symbol.", ClueType::Physical);
	SpecialNPC General_Blackthorn("General Blackthorn", "Cedric was always looked up upon almost as an Idol upon the Humans. But the Reptiles... especially Snakekind... I would say not so much.");

	//Library
	Clue messyBooks("Messy Books", "The Library seems odd... All the books are arranged wrongly... Does the Librarian know what she is doing..?", ClueType::Physical);
	Clue Newspaper("Newspaper", "Arcania has been burnt to smithereens by the Red Dragon... All surviving refugees are fleeing to Arcadia.", ClueType::Physical);
	SpecialNPC Isabella_Nightshade("Isabella Nightshade", "The Forbidden Section? Sssso far, I only know 4 people with accesssss to it.");

	//Shop
	Clue weirdAura("Weird Aura", "This shop... there's so many strange items being sold... What's a one sided coin ever going to be used for..?", ClueType::Physical);
	SpecialNPC Aurelius_Mindweaver("Aurelius Mindweaver", "The Forbidden Section of the Archives? I only know 2 other people who has access to it.");

	//Str's House
	SpecialNPC Valeria_Stormbringer("Valeria Stormbringer", "The Forbidden Section of the Archives? I only know 2 other people who has access to it.");

	//Luk's House
	SpecialNPC Seraphina_Fortuna("Seraphina Fortuna", "The Forbidden Section of the Archives? I only know 2 other people who has access to it.");

	//Library Forbidden
	Clue weirdBook("A Book with torn pages", "The book... has the section of Possession and Deception torn out...!!", ClueType::Physical);
	Clue snakeSkin("Snake Skin", "There seems to be dried up Snake Skin on the floor...", ClueType::Physical);

	ConclusiveClue ImposterLibrarian("Imposter Librarian", "The bloody knife and witness testimony indicate the direction the culprit likely escaped.");

	CluePuzzle newPuzzle;

	newPuzzle.AddConclusiveClue(&ImposterLibrarian);

	std::vector<SpecialNPC> Characters = { Cedric_Everhart, General_Blackthorn, Isabella_Nightshade, Aurelius_Mindweaver, Valeria_Stormbringer, Seraphina_Fortuna };

	while (true)
	{
		ShowScrollBar(GetConsoleWindow(), SB_BOTH, false);
		if (States == EXPLORATION)
		{
			Utility::PositionText(0, 0);
			SetConsoleTextAttribute(outputHandle, 15);
			std::cout << "+======================================================================================================================+" << std::endl;

			switch (newMap.getCurrentDoor())
			{
			 case WORLD:
				 std::cout << Magenta << " ARCADIA" << ResetColour << " | " << Cyan << "OPEN WORLD" << ResetColour << std::endl;
				break;
			 case DETECTIVE_ROOM:
				 std::cout << Magenta << " ARCADIA" << ResetColour << " | " << Cyan << "CHIEF GENERAL'S OFFICE" << ResetColour << std::endl;
				 break;
			 case LIBRARY:
				 std::cout << Magenta << " ARCADIA" << ResetColour << " | " << Cyan << "THE ARCHIVES" << ResetColour << std::endl;
				 break;
			 case LIBRARY_FORBIDDEN:
				 std::cout << Magenta << " ARCADIA" << ResetColour << " | " << Cyan << "THE ARCHIVES, FORBIDDEN SECTION" << ResetColour << std::endl;
				 break;
			 case SHOP:
				 std::cout << Magenta << " ARCADIA" << ResetColour << " | " << Cyan << "WIZARDLY OFFERINGS" << ResetColour << std::endl;
				 break;
			 case STRENGTH_HOUSE:
				 std::cout << Magenta << " ARCADIA" << ResetColour << " | " << Cyan << "VALERIA STORMBRINGER'S ABODE" << ResetColour << std::endl;
				 break;
			 case LUCK_HOUSE:
				 std::cout << Magenta << " ARCADIA" << ResetColour << " | " << Cyan << "SERAPHINE FORTUNA'S ABODE" << ResetColour << std::endl;
				 break;
			}

			std::cout << "+======================================================================================================================+" << std::endl;

			COORD statCoordinates = { 0, 3 };
			SetConsoleCursorPosition(outputHandle, statCoordinates);
			for (int i = 0; i < 2; i++) {
				if (Plr[i] != nullptr) {
					Plr[i]->displaystats();
				}
				statCoordinates.Y++;
				SetConsoleCursorPosition(outputHandle, statCoordinates);
			}
			
			std::cout << "+======================================================================================================================+" << std::endl;

			Utility::PositionText(7, 6);
			std::cout << "+====+< KEYBINDS >+====+ ";

			Utility::PositionText(7, 8);
			std::cout << "+ MOVEMENT +";

			Utility::PositionText(6, 9);
			std::cout << "[W] - Move Up";
			Utility::PositionText(6, 10);
			std::cout << "[A] - Move Left";
			Utility::PositionText(6, 11);
			std::cout << "[S] - Move Down";
			Utility::PositionText(6, 12);
			std::cout << "[D] - Move Right";

			Utility::PositionText(7, 14);
			std::cout << "+ INVENTORY +";

			Utility::PositionText(6, 15);
			std::cout << "[I] - Open/Close Inventory";
			Utility::PositionText(6, 16);
			std::cout << "[<] - Navigate Items";
			Utility::PositionText(6, 17);
			std::cout << "[>] - Navigate Items";
			Utility::PositionText(6, 18);
			std::cout << "[E] - Place Item";
			Utility::PositionText(6, 19);
			std::cout << "[O] - Delete Item";

			Utility::PositionText(7, 21);
			std::cout << "+ OTHERS +";

			Utility::PositionText(6, 22);
			std::cout << "[F] - Interaction";

			Utility::PositionText(91, 6);
			std::cout << "+=====+< LEGEND >+=====+ ";

			Utility::PositionText(91, 8);
			std::cout << "+ WORLD +";

			Utility::PositionText(91, 9);
			std::cout << "[X] - Grass";

			Utility::PositionText(0, 25);
			std::cout << "+======================================================================================================================+" << std::endl;

			if (map_Loaded == true && text_Loaded == false)
			{
				text_Loaded = true;
				SetConsoleTextAttribute(outputHandle, 15);
				Utility::PositionText(0, 28);
				Utility::typewriterText(newMap.getCurrentRoomText1(), 10);
				Utility::PositionText(0, 29);
				Utility::typewriterText(newMap.getCurrentRoomText2(), 10);
				Utility::PositionText(0, 30);
				Utility::typewriterText(newMap.getCurrentRoomText3(), 10);
			}

			Utility::PositionText(0, 33);
			std::cout << "+======================================================================================================================+" << std::endl;

			if (map_Loaded == false) {
				system("cls");
				newMap.setMap(newMap.getCurrentDoor());
				Utility::SetupFont(30);
				Utility::ShowConsoleCursor(false);
				newMap.GenerateGrid();
				map_Loaded = true;
				text_Loaded = false;
			}
			if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState('A') || GetAsyncKeyState('D')) {

				if (GetAsyncKeyState('W') || 
					GetAsyncKeyState('S') || 
					GetAsyncKeyState('A') || 
					GetAsyncKeyState('D')) 
				{
					system("cls");
					Utility::ShowConsoleCursor(false);
					newMap.GenerateGrid();

					if (GetAsyncKeyState('S')) {
						newMap.Move(0, 1, States, enemyID);
					}
					if (GetAsyncKeyState('W')) {
						newMap.Move(0, -1, States, enemyID);
					}
					if (GetAsyncKeyState('A')) {
						newMap.Move(-1, 0, States, enemyID);
					}
					if (GetAsyncKeyState('D')) {
						newMap.Move(1, 0, States, enemyID);
					}
				}
			}

			if (GetAsyncKeyState('I')) {

				system("cls");
				((Main_character*)Plr[0])->inv(2, 2, "hello", Utility::randomNumber(1, 9));
			}

			if (GetAsyncKeyState('J')) {

				system("cls");
				newPuzzle.ViewJournal();
				map_Loaded = false;
			}

			if (GetAsyncKeyState('F')) //Interaction Key
			{
				//Order of Importance NPC -> OBJECT
				if (newMap.checkSpecialNPC(DialogueNPC, QuestionsFileStr, ResponsesFileStr) == true)
				{
					States = DIALOGUE;
					system("cls");
				}
				if (newMap.checkNPC() == true)
				{
					States = DIALOGUE;
					system("cls");
				}
				else if (newMap.checkObject("CLUE") == true)
				{
					newMap.checkObject("CLUE");
					//Clues
					switch (newMap.getCurrentClue())
					{
					case DEAD_BODY:
						newPuzzle.AddClue(&deadBody);
						newPuzzle.UpdateJournal("CLUE | Inspected Cedric Everhart's Corpse. Strange Markings on Bloodshot eyes.");
						break;
					case WAR_HERO_PHOTO:
						newPuzzle.AddClue(&heroPhoto);
						newPuzzle.UpdateJournal("CLUE | Inspected the Photo Frame in General Blackthorn's room. Cedric was such a great guy.");
						break;
					case MESSY_BOOKS:
						newPuzzle.AddClue(&messyBooks);
						newPuzzle.UpdateJournal("CLUE | The Library looks different from when I last visited... Everything is messy and unorganised.");
						break;
					case NEWSPAPERS:
						newPuzzle.AddClue(&Newspaper);
						newPuzzle.UpdateJournal("CLUE | Arcania has been burnt to smithereens by the Red Dragon... All surviving refugees are fleeing to Arcadia.");
						break;
					case COIN:
						newPuzzle.AddClue(&weirdAura);
						newPuzzle.UpdateJournal("CLUE | There are so many weird things being sold in this Shop... What is a One-Sided coin ever going to be used for..?");
						break;
					case MISSING_PAGES:
						newPuzzle.AddClue(&weirdBook);
						newPuzzle.UpdateJournal("CLUE | The all powerful book... seems to be missing some pages in the 'Possession' and 'Deception' section...");

						break;
					case SNAKE_SKIN:
						newPuzzle.AddClue(&snakeSkin);
						newPuzzle.UpdateJournal("CLUE | There seems to be Snakeskin all over the Forbidden Section of the Library...");
						break;
					}

					Utility::PositionText(0, 29);
					Utility::typewriterText(" You found a Clue! You instinctively took out your Journal and jotted it down...", 10);
				}
				else if (newMap.checkObject("DOOR") == true)
				{
					newMap.checkObject("DOOR");
					map_Loaded = false;
				}
			}
			//Sleep(10);
		}
		else if (States == DIALOGUE)
		{
			Dialogue* newDialogue = new Dialogue("[Arcadia's Tomekeeper] Isabella Nightshade", "Isabella Questions.txt", "Isabella Responses.txt");
			newDialogue->InitDialogue();
			if (newDialogue->getBreakDialogue() == true)
			{
				delete newDialogue;
				newDialogue = nullptr;

				map_Loaded = false; //Offload Map
				system("cls");
				States = EXPLORATION;
			}
		}
		else if (States == COMBAT)
		{
			((Main_character*)Plr[0])->CalculateStats();
			system("cls");
			Utility::SetupFont(40);
			while (1) {
				//for controlling turn order . value increments up to 100 first to 100 gets turn
				//speed caries over from previous turns of opponent
				if (Placeholder_Enemy[enemyID]->CheckCR()) {
					break;
				}

				if (crParty(Plr)) {
					break;
				}
			}
			if (Placeholder_Enemy[enemyID]->getTurn() == true)//enemies turn
			{
				Plr[0]->GenerateUI(*Placeholder_Enemy[enemyID]);
				Placeholder_Enemy[enemyID]->ExecuteSkill(Plr[0], Placeholder_Enemy[enemyID]->ChooseAction());
				Dodge::enemyCollided = true;
				Placeholder_Enemy[enemyID]->setTurn(false);

			}
			for (int i = 0; i < max_Party_size; i++) {
				if (Plr[i] != nullptr) {
					if (Plr[i]->getTurn() == true) {
						if (i == 0) {
							(Plr[i])->ExecuteSkill(Placeholder_Enemy[enemyID], Plr[i]->PlayerTurn(Placeholder_Enemy[enemyID]));
						}
						else {
							Plr[i]->ExecuteSkill(Placeholder_Enemy[enemyID], Plr[i]->PlayerTurn(Placeholder_Enemy[enemyID]));

						}
						Plr[i]->setTurn(false);
						break;

					}
				}
			}
			if (Placeholder_Enemy[enemyID]->getHP() <= 0) {
				std::cout << "enemy killed!";
				States = EXPLORATION;

			}
			for (int i = 0; i < max_Party_size; i++) {
				if (Plr[i] != nullptr) {
					if (Plr[i]->getHP() <= 0) {
						std::cout << Plr[i]->getName() << " killed!";

						//lose game
						system("cls");
						return 0;

						States = EXPLORATION;
						break;

					}
				}
			}
			Sleep(2000);
			system("cls");
		}
		else if (States == ITEM)
		{
			

			//int playerChoice;
			//while (true) {
			//	system("pause");
			//	DisplayUI(puzzle, characters);

			//	std::cout << "\nSelect an action:\n";
			//	std::cout << "1. Question a character\n";
			//	std::cout << "2. Combine clues\n";
			//	std::cout << "3. Form conclusion\n";
			//	std::cout << "4. Quit\n";

			//	playerChoice = GetPlayerChoice(1, 18);

			//	switch (playerChoice) {
			//	case 1: {
			//		std::cout << "Select a character to question:\n";
			//		for (int i = 0; i < characters.size(); ++i) {
			//			std::cout << i + 1 << ". " << characters[i].name << "\n";
			//		}
			//		int characterChoice = GetPlayerChoice(1, characters.size()) - 1;
			//		puzzle.GatherClue(new Clue(characters[characterChoice].name + "'s Testimony", characters[characterChoice].testimony, ClueType::Testimonial));

			//		journal.AddEntry("Questioned a character");
			//		break;
			//	}
			//	case 2: {
			//		std::cout << "Select two clues to combine:\n";

			//		// Display available clues for selection
			//		for (int i = 0; i < puzzle.gatheredClues.size(); ++i) {
			//			std::cout << i + 1 << ". " << puzzle.gatheredClues[i]->name << "\n";
			//		}

			//		// Get player's choices
			//		int clueIndex1, clueIndex2;
			//		do {
			//			std::cout << "Enter the index of the first clue: ";
			//			std::cin >> clueIndex1;
			//		} while (clueIndex1 < 1 || clueIndex1 > puzzle.gatheredClues.size());

			//		do {
			//			std::cout << "Enter the index of the second clue: ";
			//			std::cin >> clueIndex2;
			//		} while (clueIndex2 < 1 || clueIndex2 > puzzle.gatheredClues.size() || clueIndex2 == clueIndex1);

			//		// Get the selected clues
			//		Clue* selectedClue1 = puzzle.gatheredClues[clueIndex1 - 1];
			//		Clue* selectedClue2 = puzzle.gatheredClues[clueIndex2 - 1];

			//		// Combine selected clues
			//		if (selectedClue1->type == ClueType::Physical && selectedClue2->type == ClueType::Physical) {
			//			std::cout << "Combining " << selectedClue1->name << " and " << selectedClue2->name << "...\n";
			//			std::cout << "Deduction: The physical evidence supports the witness testimony.\n";
			//			// Optionally, you can add more complex deduction logic here
			//		}
			//		else if (selectedClue1->type == ClueType::Testimonial && selectedClue2->type == ClueType::Physical) {
			//			std::cout << "Combining " << selectedClue1->name << " and " << selectedClue2->name << "...\n";
			//			std::cout << "Deduction: The witness testimony corroborates the physical evidence.\n";
			//			// Optionally, you can add more complex deduction logic here
			//		}
			//		else {
			//			std::cout << "The selected clues cannot be combined in this way.\n";
			//		}
			//		journal.AddEntry("Combined clues!");
			//		break;
			//	}
			//	case 3: {
			//		puzzle.FormConclusion("Culprit's Motive");
			//		break;
			//	}
			//	case 4:
			//		std::cout << "Exiting the game.\n";
			//		break;
			//	case 5:
			//		// View journal
			//		journal.DisplayJournalPage(currentPage);
			//		break;
			//	case 6: {
			//		// Search journal
			//		std::string keyword;
			//		std::cout << "Enter keyword to search: ";
			//		std::cin.ignore();
			//		std::getline(std::cin, keyword);
			//		journal.SearchJournal(keyword);
			//		break;
			//	}
			//	case 18:
			//		// Increment to the next page
			//		currentPage++;
			//		break;
			//		// ... Handle other cases
			//	}
			//} while (playerChoice != 4);
		}
		else if (States == EXIT)
		{
			std::cout << "\033[1;31mProgram Terminated.\033[0m";
			return 0;
		}
		else if (States == RESET)
		{
			break;
		}
	}
}