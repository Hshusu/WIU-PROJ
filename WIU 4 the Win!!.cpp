#include <iostream>
#include <random>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <cwchar>

#include "Utility.h"

#include "Player.h"

//Exploration
#include "Map.h"
#include "Location.h"

//Combat
#include "Entity.h"
#include "Npc.h"

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
	int States = EXPLORATION;

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

	Player* Plr[max_Party_size] = { nullptr };
	Plr[0] = new Player(PMods, "Marcus", Lightning, Ice);
	Plr[1] = new Player("Remus", 1.1, 10, 1.3, 20, Fire, Darkness);
	NPC* Placeholder_Enemy = new NPC("placeholder", 2, 10, 1.1, 20, Fire, Darkness);

	while (true)
	{
		//system("cls");

		if (States == EXPLORATION)
		{
			if (map_Loaded == false) {
				Utility::SetupFont(20);
				newMap.GenerateGrid();
				newMap.UpdatePlayer();
				map_Loaded = true;
			}
			if (GetAsyncKeyState('F')) {
				newMap.GenerateGrid();
			}
			if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState('A') || GetAsyncKeyState('D')) {
				system("cls");
				Utility::ShowConsoleCursor(false);
				newMap.GenerateGrid();
				newMap.UpdatePlayer();
				if (GetAsyncKeyState('S')) {
					newMap.Move(0, 1);
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
			Dialogue* newDialogue = new Dialogue("[Tevyat Townsfolk] The Debug NPC", "Test Questions.txt", "Test Responses.txt");
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
			Plr[0]->CalculateStats();
			system("cls");
			Utility::SetupFont(50);
			while (1) {
				//for controlling turn order . value increments up to 100 first to 100 gets turn
				//speed caries over from previous turns of opponent
				if (Placeholder_Enemy->CheckCR()) {
					break;
				}

				if (crParty(Plr)) {
					break;
				}
			}
			if (Placeholder_Enemy->getTurn() == true)//enemies turn
			{
				Plr[0]->GenerateUI(*Placeholder_Enemy);
				Placeholder_Enemy->ExecuteSkill(Plr[0], Placeholder_Enemy->ChooseAction());
				Placeholder_Enemy->setTurn(false);

			}
			for (int i = 0; i < max_Party_size; i++) {
				if (Plr[i] != nullptr) {
					if (Plr[i]->getTurn() == true) {

						Plr[i]->ExecuteSkill(Placeholder_Enemy, Plr[i]->PlayerTurn(Placeholder_Enemy));
						Plr[i]->setTurn(false);
						break;

					}
				}
			}
			if (Placeholder_Enemy->getHP() <= 0) {
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