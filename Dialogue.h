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

#include "Utility.h"

class Dialogue
{
private:
	static bool DialogueStatus;

	Dialogue* PreviousChoice;
	std::string* ChoiceText;
	Dialogue* currentDialogue;

	int dialogueState;
	int rowCounter;

	std::string questions_FileString;
	std::string responses_FileString;

	std::string dialogueID;
	std::string questionsLine;
	std::string responsesLine;

	std::string Options[4] = { (std::string)Green + "[ 1 ]" + ResetColour, "[ 2 ]", "[ 3 ]", "[ 4 ]" };
public:
	static bool getDialogueStatus(void);

	void InitDialogue();

	Dialogue(std::string dialogueID, std::string Questions_FileString, std::string Responses_FileString);
	Dialogue(std::string Input1, std::string Input2);

	~Dialogue();
};

