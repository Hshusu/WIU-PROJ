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

enum StateNames
{
	//Main
	EXPLORATION,
	WEAPON,
	INVENTORY,
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
	int States = COMBAT;

	//General
	COORD Screen;
	Utility::MaxScreen();
	//Exploration
	bool map_Loaded = false;
	Map newMap(1);

	//Dialogue
	std::string DialogueNPC, QuestionsFileStr, ResponsesFileStr;

	//Combat
	const int max_Party_size = 4;
	float PMods[6] = { 1,1,1,1,1,1 };
	int enemyID=3;
	Player* Plr[max_Party_size] = { nullptr };
	Plr[0] = new Main_character(PMods, "Marcus", Lightning, Ice);
	Plr[1] = new Player("Remus", 1.1, 10, 2, 20, Fire, Darkness);
	NPC* Placeholder_Enemy[10] = { nullptr };
	Placeholder_Enemy[0] = new NPC("placeholder", 2, 10, 1.5, 20, Fire, Darkness);
	Placeholder_Enemy[1] = new NPC("kk", 2, 10, 1.5, 20, Fire, Darkness);
	Placeholder_Enemy[2] = new NPC("hshusu", 2, 10, 1.5, 20, Fire, Darkness);
	Placeholder_Enemy[3] = new NPC("blade", 2, 10, 1.5, 20, Fire, Darkness);

	//inventory
		

	while (true)
	{
		ShowScrollBar(GetConsoleWindow(), SB_BOTH, false);
		

		if (States == EXPLORATION)
		{
			if (map_Loaded == false) {
				Utility::SetupFont(20);
				newMap.GenerateGrid();
				map_Loaded = true;
			}
			if (GetAsyncKeyState('F')) {
				newMap.GenerateGrid();
			}
			if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState('A') || GetAsyncKeyState('D')
				|| GetAsyncKeyState('K') || GetAsyncKeyState('P')) {
				system("cls");
				Utility::ShowConsoleCursor(false);
				newMap.GenerateGrid();
				
				if (GetAsyncKeyState('S')) {
					newMap.Move(0, 1);
				}
				if (GetAsyncKeyState('K')) {
					
					((Main_character*)Plr[0])->inv(2, 2, "hello", Utility::randomNumber(1,9));
					system("cls");
					Utility::ShowConsoleCursor(false);
					newMap.GenerateGrid();
				}
				if (GetAsyncKeyState('P')) {

					((Main_character*)Plr[0])->inv();
					system("cls");
					Utility::ShowConsoleCursor(false);
					newMap.GenerateGrid();
				}
				if (GetAsyncKeyState('W')) {
					newMap.Move(0, -1);
				}
				if (GetAsyncKeyState('A')) {
					newMap.Move(-1, 0);
				}
				if (GetAsyncKeyState('D')) {
					newMap.Move(1, 0);
				}
			}
			if (GetAsyncKeyState('X')) //Interaction Key
			{
				newMap.checkNPC();
			}
		}
		else if (States == DIALOGUE)
		{
			Dialogue* newDialogue = new Dialogue("[Arcadia's Tomekeeper] Isabella Nightshade", "Isabella Questions.txt", "Isabella Responses.txt");
			newDialogue->InitDialogue();
			if (newDialogue->getDialogueStatus() == false)
			{
				delete newDialogue;
				newDialogue = nullptr;

				States = 0;
			}
		}
		else if (States == COMBAT)
		{

			((Main_character*)Plr[0])->CalculateStats();
			system("cls");
			Utility::SetupFont(20);
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
						else {Plr[i]->ExecuteSkill(Placeholder_Enemy[enemyID], Plr[i]->PlayerTurn(Placeholder_Enemy[enemyID]));
					
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
			//Clue bloodyKnife("Bloody Knife", "A knife with traces of blood near the crime scene.", ClueType::Physical);
			//Clue tornNote("Torn Note", "A torn note with partial text mentioning a meeting at midnight.", ClueType::Physical);
			//Character john("John", "I heard a loud noise and saw someone running away from the crime scene.");
			//Character emily("Emily", "I wasn't at the crime scene, I was at a coffee shop all night.");
			//ConclusiveClue escapeRoute("Culprit's Escape Route", "The bloody knife and witness testimony indicate the direction the culprit likely escaped.");
			//ConclusiveClue alibiContradiction("Alibi Contradiction", "The torn note suggests an alibi contradiction for suspect Emily's claim of being at a coffee shop.");
			//ConclusiveClue burglaryConnection("Burglary Connection", "The broken window and stolen jewelry indicate a burglary motive for the crime.");

			//Puzzle puzzle;
			//puzzle.GatherClue(&bloodyKnife);
			//puzzle.GatherClue(&tornNote);
			//puzzle.AddConclusiveClue(&escapeRoute);
			//puzzle.AddConclusiveClue(&alibiContradiction);
			//puzzle.AddConclusiveClue(&burglaryConnection);

			//std::vector<Character> characters = { john, emily };

			//PlayerJournal journal(5); // 5 entries per page

			//int currentPage = 1;

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