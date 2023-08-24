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

#include "Shop.h"

#pragma comment(lib, "Winmm.lib")

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

	int CutsceneCounter1 = 0, CutsceneCounter2 = 0, CutsceneCounter3 = 0;
	bool beginningCutscene = true;
	bool midwayCutscene = true;
	bool endingCutscene = true;

	//Exploration
	bool map_Loaded = false;
	bool text_Loaded = false;
	Map newMap;

	//Dialogue
	std::string DialogueNPC, QuestionsFileStr, ResponsesFileStr;

	int correctClueCounter = 0;

	//Combat
	bool hostilityEnabled = true;
	bool combatEnabled = false;
	const int max_Party_size = 4;
	float PMods[6] = { 1.5,1.6,1.1,1.6,1.4,1 };
	int enemyID = 2;
	const int enemycount = 10;
	Player* Plr[max_Party_size] = { nullptr };
	Plr[0] = new Main_character(PMods, "You", Lightning, Ice);
	Plr[1] = new Player("Your Partner", 1.2, 50, 1.3, 20, Fire, Darkness);
	NPC* Placeholder_Enemy[enemycount] = { nullptr };
	Placeholder_Enemy[0] = new NPC("Rogue Goblin", 2, 10, 1.5, 20, Fire, Ice);
	Placeholder_Enemy[1] = new NPC("Rogue Elf", 2, 10, 1.5, 20, Fire, Darkness);
	Placeholder_Enemy[2] = new NPC("Rogue Orc", 2, 10, 1.5, 20, Fire, Darkness);
	Placeholder_Enemy[3] = new NPC("Rogue Serpent", 2, 10, 1.6, 20, None, Darkness);
	Placeholder_Enemy[4] = new NPC("Isabella Nightshade [Reptilian]", 2, 50, 1.6, 150, Fire, Darkness);

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

	ConclusiveClue ImposterLibrarian("Imposter Librarian", "The Librarian mind controlled the Mayor to kill himself during the rally.");

	ConclusiveClue ImposterGeneral("Imposter General", "The General was corrupt and manipulated you all along to get access to the Forbidden Area");

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
				 std::cout << White << " ARCADIA" << ResetColour << " | " << Cyan << "OPEN WORLD" << ResetColour << std::endl;
				break;
			 case DETECTIVE_ROOM:
				 std::cout << White << " ARCADIA" << ResetColour << " | " << Cyan << "CHIEF GENERAL'S OFFICE" << ResetColour << std::endl;
				 break;
			 case LIBRARY:
				 std::cout << White << " ARCADIA" << ResetColour << " | " << Cyan << "THE ARCHIVES" << ResetColour << std::endl;
				 break;
			 case LIBRARY_FORBIDDEN:
				 std::cout << White << " ARCADIA" << ResetColour << " | " << Cyan << "THE ARCHIVES, FORBIDDEN SECTION" << ResetColour << std::endl;
				 break;
			 case SHOP:
				 std::cout << White << " ARCADIA" << ResetColour << " | " << Cyan << "WIZARDLY OFFERINGS" << ResetColour << std::endl;
				 break;
			 case STRENGTH_HOUSE:
				 std::cout << White << " ARCADIA" << ResetColour << " | " << Cyan << "VALERIA STORMBRINGER'S ABODE" << ResetColour << std::endl;
				 break;
			 case LUCK_HOUSE:
				 std::cout << White << " ARCADIA" << ResetColour << " | " << Cyan << "SERAPHINE FORTUNA'S ABODE" << ResetColour << std::endl;
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

			Utility::PositionText(60, 3);
			std::cout << "||  " << Cyan << "LEVEL" << ResetColour << ": " << ((Main_character*)Plr[0])->getPlayerLevel() << " | " << Cyan << "EXP" << ResetColour ": " << ((Main_character*)Plr[0])->getPlayerExp() << " / 100";
			Utility::PositionText(60, 4);
			int barWidth = 54;

			float width = barWidth * ((Main_character*)Plr[0])->getPlayerExp() / 100.0f;

			std::cout << "|| [";
			for (int i = 0; i < barWidth; ++i) {
				if (i < width)
				{
					std::cout << Cyan << "=" << ResetColour;
				}
				else std::cout << " ";
			}
			std::cout << "] " << std::endl;

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
			std::cout << "[UP] - Navigate Items";
			Utility::PositionText(6, 17);
			std::cout << "[DOWN] - Navigate Items";
			Utility::PositionText(6, 18);
			std::cout << "[E] - Place Item";
			Utility::PositionText(6, 19);
			std::cout << "[R] - Rotate Item";
			Utility::PositionText(6, 20);
			std::cout << "[O] - Delete Item";

			Utility::PositionText(7, 22);
			std::cout << "+ OTHERS +";

			Utility::PositionText(6, 23);
			std::cout << "[F] - Interaction";
			Utility::PositionText(6, 24);
			std::cout << "[J/M] - Open/Close Journal";

			Utility::PositionText(91, 6);
			std::cout << "+=====+< LEGEND >+=====+ ";

			Utility::PositionText(92, 8);
			std::cout << "+ WORLD +";

			Utility::PositionText(91, 9);
			std::cout << "[X] - Grass";

			Utility::PositionText(91, 10);
			std::cout << "[D] - Doors";

			Utility::PositionText(92, 12);
			std::cout << "+ MAIN NPCS +";

			Utility::PositionText(91, 13);
			std::cout << "[G] - General Blackthorn";

			Utility::PositionText(91, 14);
			std::cout << "[I] - Isabella Nightshade";

			Utility::PositionText(91, 15);
			std::cout << "[S] - Shopkeeper";

			Utility::PositionText(91, 16);
			std::cout << "[V] - Valeria Stormbringer";

			Utility::PositionText(91, 17);
			std::cout << "[S] - Seraphina Fortuna";

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

			while (beginningCutscene == true)
			{
				std::string storyText1, storyText2, storyText3, storyText4, storyText5;
				switch (CutsceneCounter1)
				{
				case 0:
					storyText1 = "The sounds of heavy downpour was drowned out by the rabid enthsuiasm of the crowd. Yet, The crowd was not";
					storyText2 = "too particularly concerned. From Human Blacksmiths to High Elf Book Keepers, They had gathered to watch";
					storyText3 = "Cedric Everhart, the Electing Governer of Arcadia, rewrite history. He had envisioned a world where both";
					storyText4 = "humans and beastfolk could live in harmony. With the new set of laws he was about to propose, the Fate of";
					storyText5 = "Arcadia would forever be altered.";
					break;
				case 1:
					storyText1 = "'I'm honored that such a crowd has gathered here in support of a better future..' The man of the hour announced.";
					storyText2 = "These words did not merely belong to the Govenor, but a Famed War Hero. They probably had no interest in the presence of";
					storyText3 = "the washed up General, turned Detective who stood in the corner. He had been hired to act as Cedric's bodyguard";
					storyText4 = "personally by the man himself. They had met during the war and stayed close friends after for their shared wish for";
					storyText5 = "peace between the nations. Cedric wanted to give his old friend a chance to witness the birth of a new Era of Peace.";
					break;
				case 2:
					storyText1 = "'Once this law is in placed, the citizens of this great land shall become united and equal and we shall begin the long";
					storyText2 = "process of recovery for both countri - arghhhhHH'. Governor Cedric's rich mahogony eyes glowed an iridescent purple and";
					storyText3 = "with little foreshadowing, slit his throat using the very dagger he had once used to to execute the general of the";
					storyText4 = "Empire. The horde went in a panic in terror, quickly devolving into a racial mobs, with each side condemming the other.";
					storyText5 = "I rushed to the side of my dying comrade in a hurry. He uttered his last words... 'The Enchiridean...'";
					break;
				}

				if (CutsceneCounter1 >= 3)
				{
					beginningCutscene = false;
					CutsceneCounter1 = 0;
				}
				else
				{
					SetConsoleTextAttribute(outputHandle, 15);
					Utility::SetupFont(30);
					Utility::PositionText(2, 26);
					Utility::typewriterText(storyText1, 10);
					Utility::PositionText(2, 27);
					Utility::typewriterText(storyText2, 10);
					Utility::PositionText(2, 28);
					Utility::typewriterText(storyText3, 10);
					Utility::PositionText(2, 29);
					Utility::typewriterText(storyText4, 10);
					Utility::PositionText(2, 30);
					Utility::typewriterText(storyText5, 10);
					Utility::PositionText(2, 32);
					system("pause");
					CutsceneCounter1++;
					storyText1 = "                                                                                                                                       ";
					storyText2 = "                                                                                                                                       ";
					storyText3 = "                                                                                                                                       ";
					storyText4 = "                                                                                                                                       ";
					storyText5 = "                                                                                                                                       ";
					Utility::PositionText(2, 26);
					Utility::typewriterText(storyText1, 0);
					Utility::PositionText(2, 27);
					Utility::typewriterText(storyText2, 0);
					Utility::PositionText(2, 28);
					Utility::typewriterText(storyText3, 0);
					Utility::PositionText(2, 29);
					Utility::typewriterText(storyText4, 0);
					Utility::PositionText(2, 30);
					Utility::typewriterText(storyText5, 0);
					Utility::PositionText(2, 32);
				}
			}
			if (map_Loaded == false) {
				system("cls");
				newMap.setMap(newMap.getCurrentDoor());
				Utility::SetupFont(30);
				Utility::ShowConsoleCursor(false);
				newMap.GenerateGrid();
				map_Loaded = true;
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

			//Interaction Keys
			if (GetAsyncKeyState('J')) {

				system("cls");
				newPuzzle.ViewJournal();
				map_Loaded = false;
			}

			if (GetAsyncKeyState('F'))
			{
				if (newMap.checkSpecialNPC(DialogueNPC, QuestionsFileStr, ResponsesFileStr, combatEnabled, enemyID, States, hostilityEnabled) == true)
				{
					system("cls");
				}
				if (newMap.checkNPC() == true)
				{
					States = DIALOGUE;
					system("cls");
				}
				else if (newMap.checkObject("CLUE", States) == true)
				{
					newMap.checkObject("CLUE", States);
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
				else if (newMap.checkObject("DOOR", States) == true)
				{
					newMap.checkObject("DOOR", States);
					map_Loaded = false;
					text_Loaded = false;
				}
			}
			Sleep(10);
		}
		else if (States == DIALOGUE)
		{
			Dialogue* newDialogue = new Dialogue(DialogueNPC, QuestionsFileStr, ResponsesFileStr);
			newDialogue->InitDialogue(combatEnabled, hostilityEnabled);
			if (newDialogue->getBreakDialogue() == true)
			{
				delete newDialogue;
				newDialogue = nullptr;

				map_Loaded = false; //Offload Map
				system("cls");
				if (combatEnabled == true)
				{
					States = COMBAT;
				}
				else
				{
					States = EXPLORATION;
				}

				//Story purposes
				if (DialogueNPC == "Arcadia's Mighty Warden | Valeria Stormbringer [ORC]")
				{
					newMap.setDefeatedValeria(true);
				}
			}
		}
		else if (States == COMBAT)
		{
			((Main_character*)Plr[0])->CalculateStats();
			//enemyID = 4;
			system("cls");
			Utility::SetupFont(30);
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
				Placeholder_Enemy[enemyID]->ExecuteSkill(Plr[Utility::randomNumber(0, 1)], Placeholder_Enemy[enemyID]->ChooseAction());
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
				Placeholder_Enemy[enemyID]->resethp();

				//plr rewards
				((Main_character*)Plr[0])->setPlayerExp(50, States);

			}
			for (int i = 0; i < max_Party_size; i++) {
				if (Plr[i] != nullptr) {
					if (Plr[i]->getHP() <= 0) {
						std::cout << Plr[i]->getName() << " killed!";
						Sleep(20000);
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
		else if (States == STORE)
		{
			Shop newShop;
			newShop.addItem("Health Potion", 5, 10);
			newShop.addItem("Mana Potion", 5, 15);
			newShop.addItem("Stats Potion", 5, 15);
			newShop.addItem("One Sided Coin", 1, 15);

			int choice;
			do {
				choice = newShop.displayItemsAndGetChoice();

				if (choice < newShop.getNumItems()) {
					if (newShop.buyItem(choice, 1)) {
						std::cout << "Purchase successful!\n";
						
						std::cout << "You bought " << 1 << " " << newShop.getItemName(choice) << "(s) for $" << (newShop.getItemPrice(choice)) << ".\n";

						if (newShop.getItemName(choice) == "One Sided Coin")
						{
							newMap.setCoinBought(true);
						}
						else if (newShop.getItemName(choice) == "Health Potion")
						{
							((Main_character*)Plr[0])->HealthPotCounter();
							 system("cls");
							((Main_character*)Plr[0])->inv(2, 3, "Health Potion", ((Main_character*)Plr[0])->GetHealthPotCount());
						}
						else if (newShop.getItemName(choice) == "Mana Potion")
						{
							((Main_character*)Plr[0])->ManaPotCounter();
							 system("cls");
							((Main_character*)Plr[0])->inv(3, 1, "Mana Potion", ((Main_character*)Plr[0])->GetManaPotCount());
						}
						else if (newShop.getItemName(choice) == "Stats Potion")
						{
							((Main_character*)Plr[0])->StatPotCounter();
							 system("cls");
							((Main_character*)Plr[0])->inv(3, 3, "Stat Potion", ((Main_character*)Plr[0])->GetStatPotCount());
						}
					}
					else {
						std::cout << "Purchase failed.\n";
					}
				}
				Sleep(2000);
				std::cout << "Press 'S' to close...";
				char input;
				do {
					input = _getch();
				} while (input != 'S' && input != 's');
				States = EXPLORATION;
				break;
			} while (choice < newShop.getNumItems());
		}
		else if (States == DEDUCTION)
		{
			// Display available clues for selection
			for (int i = 0; i < newPuzzle.gatheredClues.size(); ++i) {
				std::cout << i + 1 << ". " << newPuzzle.gatheredClues[i]->getName() << "\n";
			}

			// Get player's choices
			int clueIndex1, clueIndex2;
			do {
				std::cout << "Enter the index of the first clue: ";
				std::cin >> clueIndex1;
			} while (clueIndex1 < 1 || clueIndex1 > newPuzzle.gatheredClues.size());

			do {
				std::cout << "Enter the index of the second clue: ";
				std::cin >> clueIndex2;
			} while (clueIndex2 < 1 || clueIndex2 > newPuzzle.gatheredClues.size() || clueIndex2 == clueIndex1);

			// Get the selected clues
			Clue* selectedClue1 = newPuzzle.gatheredClues[clueIndex1 - 1];
			Clue* selectedClue2 = newPuzzle.gatheredClues[clueIndex2 - 1];

			if (selectedClue1->getType() == ClueType::Physical && selectedClue2->getType() == ClueType::Physical) {
				std::cout << "Combining " << selectedClue1->getName() << " and " << selectedClue2->getName() << "...\n";
				std::cout << "Deduction: The physical evidence supports the witness testimony.\n";
				newPuzzle.AddConclusiveClue(&ImposterGeneral);
				newPuzzle.AddConclusiveClue(&ImposterLibrarian);
			}

			while (midwayCutscene == true)
			{
				std::string storyText1, storyText2, storyText3, storyText4, storyText5;
				switch (CutsceneCounter2)
				{
				case 0:
					storyText1 = "The hairs around my neck perked up from the realization of the confounding truth, my eyes slowly shifting from my old";
					storyText2 = "friend to the once friendly presense behind, which was rapidly turning forboding. The clues were always there hidden";
					storyText3 = "behind the veneer of kindness, the hissing, the lapses in common knowledge, the deshavelled state of the Grand Archives";
					storyText4 = "slowly motioning towards my shortsword I warned, 'its the librarian!' in that instant, a blast of eldrich magic tore";
					storyText5 = "through the air, the crackling of pure evil energy foretelling our eminent demise.";
					break;
				case 1:
					storyText1 = "I split the vile bolt of darkness in twain. The bookshelves were forcefully and rapidly mutillated, pages spewing into";
					storyText2 = "the air, as though they were organs bursting out of bodies. The figure before me, was humble in frame yet cast";
					storyText3 = "a shadow of malice. Isabella Nightshade. 'The empire remembersssss..' Nightshade rebuttals scales gleaming in the";
					storyText4 = "light of the nearby candles. In a swift motion, she opened the Enchiridean which was previously hidden by the veil";
					storyText5 = "of an illusion. The power of thissss ancient tome, which you sssscum plundered from my homeland, I ssssshall resssssurect the great EMPIRE!!.";
					break;
				}

				if (CutsceneCounter2 >= 2)
				{
					midwayCutscene = false;
					CutsceneCounter2 = 0;
				}
				else
				{
					SetConsoleTextAttribute(outputHandle, 15);
					Utility::SetupFont(30);
					Utility::PositionText(2, 26);
					Utility::typewriterText(storyText1, 10);
					Utility::PositionText(2, 27);
					Utility::typewriterText(storyText2, 10);
					Utility::PositionText(2, 28);
					Utility::typewriterText(storyText3, 10);
					Utility::PositionText(2, 29);
					Utility::typewriterText(storyText4, 10);
					Utility::PositionText(2, 30);
					Utility::typewriterText(storyText5, 10);
					Utility::PositionText(2, 32);
					system("pause");
					CutsceneCounter2++;
					storyText1 = "                                                                                                                                       ";
					storyText2 = "                                                                                                                                       ";
					storyText3 = "                                                                                                                                       ";
					storyText4 = "                                                                                                                                       ";
					storyText5 = "                                                                                                                                       ";
					Utility::PositionText(2, 26);
					Utility::typewriterText(storyText1, 0);
					Utility::PositionText(2, 27);
					Utility::typewriterText(storyText2, 0);
					Utility::PositionText(2, 28);
					Utility::typewriterText(storyText3, 0);
					Utility::PositionText(2, 29);
					Utility::typewriterText(storyText4, 0);
					Utility::PositionText(2, 30);
					Utility::typewriterText(storyText5, 0);
					Utility::PositionText(2, 32);
				}
			}

			States = COMBAT;
			enemyID = 4;
		}
		else if (States == LEVELUP)
		{
			std::cout << R"(   _      ________      ________ _        _    _ _____  _ 
  | |    |  ____\ \    / /  ____| |      | |  | |  __ \| |
  | |    | |__   \ \  / /| |__  | |      | |  | | |__) | |
  | |    |  __|   \ \/ / |  __| | |      | |  | |  ___/| |
  | |____| |____   \  /  | |____| |____  | |__| | |    |_|
  |______|______|   \/   |______|______|  \____/|_|    (_)                                                  
)";

			Utility::PositionText(2, 7);
			std::cout << "\033[1;36mYou LEVELED UP! You get to allocate 1 Stat Point into your Current Stats.\033[0m";
			// 0 is str , 1 is dex , 2 is int , 3 is vit , 4 is lck , 5 is wis , 6 is for hp , 7 is for mana
			Utility::PositionText(2, 9);
			std::cout << "[\033[1;32m1\033[0m] Strength" << std::endl;

			Utility::PositionText(2, 10);
			std::cout << "[\033[1;32m2\033[0m] Dexterity" << std::endl;

			Utility::PositionText(2, 11);
			std::cout << "[\033[1;32m3\033[0m] Intelligence" << std::endl;

			Utility::PositionText(2, 12);
			std::cout << "[\033[1;32m4\033[0m] Vitality" << std::endl;

			Utility::PositionText(2, 13);
			std::cout << "[\033[1;32m5\033[0m] Luck" << std::endl;

			Utility::PositionText(2, 14);
			std::cout << "[\033[1;32m6\033[0m] Wisdom" << std::endl;

			Utility::PositionText(2, 16);
			std::cout << "\033[1;36mWhich Stat would you like to increment? > \033[0m";

			int chosen_Stat;

			std::cin >> chosen_Stat;

			switch (chosen_Stat) {
			case 1:
				((Main_character*)Plr[0])->character_Modifiers[0] += 1; // incrementing the player's stat
				States = EXPLORATION;
				break;
			case 2:
				((Main_character*)Plr[0])->character_Modifiers[1] += 1;
				States = EXPLORATION;
				break;
			case 3:
				((Main_character*)Plr[0])->character_Modifiers[2] += 1;
				States = EXPLORATION;
				break;
			case 4:
				((Main_character*)Plr[0])->character_Modifiers[3] += 1;
				States = EXPLORATION;
				break;
			case 5:
				((Main_character*)Plr[0])->character_Modifiers[4] += 1;
				States = EXPLORATION;
				break;
			case 6:
				((Main_character*)Plr[0])->character_Modifiers[5] += 1;
				States = EXPLORATION;
				break;
			default:
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				system("cls");
				States = LEVELUP;
				break;
			}
		}
		else if (States == EXIT)
		{
			std::cout << "\033[1;31mProgram Terminated.\033[0m";
			return 0;
		}
	}
}