#pragma once
#include "Matrix.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cwchar>
#include <random>
#include <conio.h> //For _getch()

#include "NodeTree.h"
#include "Utility.h"

class Dialogue
{
private:
	int dialogueState;
	int rowCounter;

	std::string questions_FileString;
	std::string responses_FileString;

	std::string dialogueID;
	std::string questionsLine;
	std::string responsesLine;

	std::string Options[4] = { (std::string)Green + "[ 1 ]" + ResetColour, "[ 2 ]", "[ 3 ]", "[ 4 ]" };

	bool breakDialogue = false;
public:
	void InitDialogue(bool& combatEnabled, bool& hostilityEnabled);

	bool getBreakDialogue(void) const;

	Dialogue(std::string dialogueID, std::string Questions_FileString, std::string Responses_FileString);
	~Dialogue();
};

