#include "Dialogue.h"

bool Dialogue::DialogueStatus = false;

bool Dialogue::getDialogueStatus(void)
{
    return DialogueStatus;
}

void Dialogue::InitDialogue()
{
    DialogueStatus = true;

    dialogueState = 1;
    rowCounter = 0;

    questionsLine = "";
    responsesLine = "";

    int totalQuestionLines = 0;
    int totalResponseLines = 0;

    /* Opens the file */
    std::ifstream dialogueQuestionsFile(questions_FileString);

    /* Scans entire .txt File for the total number of lines. */
    while (getline(dialogueQuestionsFile, questionsLine)) {
        totalQuestionLines++;
    }

    /* Creates a dynamic Matrix to store the texts from the .txt File. */
    Matrix* QuestionsPtr = new Matrix(totalQuestionLines, 1);

    /* Resets the .txt File read state so that it could be read again. */
    dialogueQuestionsFile.clear();
    dialogueQuestionsFile.seekg(0, dialogueQuestionsFile.beg);

    /* Temporary Questions Counter */
    int questionsCounter = 0;
    while (getline(dialogueQuestionsFile, questionsLine)) { /* Reads each line */
        /* String to hold each value */
        std::string questionsVal;

        /* Stringstream to parse fields */
        std::stringstream questionsStream(questionsLine);

        /* DEBUGGING: Outputs the original line */
        /*std::cout << "line: " << line << "\n\n";*/

        QuestionsPtr->setElement(questionsCounter, 0, questionsLine);
        questionsCounter++;
    }

    /* Closes the file */
    dialogueQuestionsFile.close();

    /* Opens the file */
    std::ifstream dialogueResponsesFile(responses_FileString);

    /* Scans entire .txt File for the total number of lines. */
    while (getline(dialogueResponsesFile, responsesLine)) {
        totalResponseLines++;
    }

    /* Resets the .txt File read state so that it could be read again. */
    dialogueResponsesFile.clear();
    dialogueResponsesFile.seekg(0, dialogueResponsesFile.beg);

    /* Creates 2 dynamic Matrices to store the texts from the .txt File. */
    Matrix* ChoicePtr = new Matrix(totalResponseLines, 1);
    Matrix* ResponsePtr = new Matrix(totalResponseLines, 1);

    while (getline(dialogueResponsesFile, responsesLine)) { /* Reads each line */
        /* String to hold each value */
        std::string responsesVal;

        /* Stringstream to parse fields */
        std::stringstream responsesStream(responsesLine);

        /* DEBUGGING: Outputs the original line */
        /*std::cout << "line: " << line << "\n\n";*/

        while (std::getline(responsesStream, responsesVal, '|'))   /* For each individual field */
        {
            /* DEBUGGING: Outputs each field value */
            /*std::cout << "  value: " << val << '\n';
            std::cout << '\n';*/

            switch (dialogueState)
            {
            case 1:
                ChoicePtr->setElement(rowCounter, 0, responsesVal);
                dialogueState++;
                break;
            case 2:
                ResponsePtr->setElement(rowCounter, 0, responsesVal);
                dialogueState = 1;
                break;
            }
            //DEBUGGING!
            /*for (int row = 0; row < test; ++row) {
                for (int col = 0; col < 1; ++col) {
                    std::cout << "Row: " << row << " Col: " << col << " " << ResponsePtr->getElement(row, col) << std::endl;
                }
            }
            for (int row = 0; row < test; ++row) {
                for (int col = 0; col < 1; ++col) {
                    std::cout << "Row: " << row << " Col: " << col << " " << QuestionPtr->getElement(row, col) << std::endl;
                }
            }*/
        }
        if (rowCounter == totalResponseLines - 1)
        {
            rowCounter = 0;
        }
        else
        {
            rowCounter++;
        }
    }

    /* Closes the file */
    dialogueResponsesFile.close();

    Matrix* PopulatedChoicePtr = new Matrix(totalResponseLines / 2, 2);
    Matrix* PopulatedResponsePtr = new Matrix(totalResponseLines / 2, 2);

    for (int i = 0; i < totalResponseLines / 2; i++)
    {
        //options
        PopulatedResponsePtr->setElement(i, 0, ResponsePtr->getElement(i * 2, 0));
        PopulatedResponsePtr->setElement(i, 1, ResponsePtr->getElement((i * 2 + 1) % totalResponseLines, 0));

        //replies
        PopulatedChoicePtr->setElement(i, 0, ChoicePtr->getElement(i * 2, 0));
        PopulatedChoicePtr->setElement(i, 1, ChoicePtr->getElement((i * 2 + 1) % totalResponseLines, 0));
    }

    //Dialogue* newDialogue = new Dialogue(QuestionsPtr, PopulatedResponsePtr, PopulatedChoicePtr);

    //New Constructor
    Utility::MaxScreen();
    Utility::SetupFont(50);

    int UserChoice = 0;
    int TempChoice = 0;

    int dialogueNumber = 1;
    int questionCounter = 0;

    const int LINELENGTH = 83;

    //Aggression
    float AggressionMeter = 100.0f;
    std::string Happy_Dialogues[3]
    {
        "I'm genuinely thrilled by our conversation!",
        "I can't help but smile when we talk.",
        "Your positivity is infectious!",
    };

    std::string Neutral_Dialogues[3]
    {
        "I'm engaged in our conversation.",
        "Let's keep the dialogue going.",
        "I'm taking in what you're saying.",
    };

    std::string Upset_Dialogues[3]
    {
        "I'm feeling a bit hurt by your actions.",
        "That wasn't very nice. It's bothering me.",
        "Your actions are affecting my mood.",
    };

    std::string Frustrated_Dialogues[3]
    {
        "I'm finding it hard to stay calm right now.",
        "I'm feeling increasingly irritated.",
        "I'm struggling to maintain my composure.",
    };

    std::string Angry_Dialogues[3]
    {
        "That's it, I've had enough. I'm getting angry now.",
        "I'm seriously upset by your repeated actions.",
        "You're pushing me to my limits. I'm really angry.",
    };

    currentDialogue = new Dialogue(ChoicePtr->getElement(0, 0), ChoicePtr->getElement(0, 1));

    while (1)
    {
        system("cls");
        //[UI] Top
        std::cout << "+-----------------------------------------------------------------------+" << std::endl;
        std::cout << " " << Cyan + dialogueID + ResetColour << std::endl;

        int barWidth = 50;

        if (AggressionMeter <= 0)
        {
            AggressionMeter = 0;
        }
        else if (AggressionMeter >= 100)
        {
            AggressionMeter = 100;
        }

        std::cout << Red << "  Aggression" << ResetColour << " | [";
        float width = barWidth * AggressionMeter / 100.0f;
        for (int i = 0; i < barWidth; ++i) {
            if (i < width)
            {
                if (AggressionMeter > 80 && AggressionMeter <= 100)
                {
                    std::cout << Green << "=" << ResetColour;
                }
                else if (AggressionMeter > 60 && AggressionMeter <= 80)
                {
                    std::cout << Green << "=" << ResetColour;
                }
                else if (AggressionMeter > 40 && AggressionMeter <= 60)
                {
                    std::cout << Yellow << "=" << ResetColour;
                }
                else if (AggressionMeter > 20 && AggressionMeter <= 40)
                {
                    std::cout << Yellow << "=" << ResetColour;
                }
                else if (AggressionMeter > 0 && AggressionMeter <= 20)
                {
                    std::cout << Red << "=" << ResetColour;
                }
            }
            else std::cout << " ";
        }
        std::cout << "] " << AggressionMeter << "%" << std::endl;
        std::cout << "+-----------------------------------------------------------------------+" << std::endl;

        //Middle
        std::string header(LINELENGTH, ' ');
        std::cout << header << '\n';

        Utility::PositionText(0, 7);
        Utility::Print(CENTRE, Cyan + dialogueID + ResetColour + "'s Thoughts:", LINELENGTH);

        if (AggressionMeter > 80 && AggressionMeter <= 100)
        {
            Utility::Print(CENTRE, "* " + (std::string)Magenta + Happy_Dialogues[Utility::randomNumber(0, 2)] + ResetColour + " *", LINELENGTH);
        }
        else if (AggressionMeter > 60 && AggressionMeter <= 80)
        {
            Utility::Print(CENTRE, "* " + (std::string)Magenta + Neutral_Dialogues[Utility::randomNumber(0, 2)] + ResetColour + " *", LINELENGTH);
        }
        else if (AggressionMeter > 40 && AggressionMeter <= 60)
        {
            Utility::Print(CENTRE, "* " + (std::string)Magenta + Upset_Dialogues[Utility::randomNumber(0, 2)] + ResetColour + " *", LINELENGTH);
        }
        else if (AggressionMeter > 20 && AggressionMeter <= 40)
        {
            Utility::Print(CENTRE, "* " + (std::string)Magenta + Frustrated_Dialogues[Utility::randomNumber(0, 2)] + ResetColour + " *", LINELENGTH);
        }
        else if (AggressionMeter > 0 && AggressionMeter <= 20)
        {
            Utility::Print(CENTRE, "* " + (std::string)Magenta + Angry_Dialogues[Utility::randomNumber(0, 2)] + ResetColour + " *", LINELENGTH);
        }
        else if (AggressionMeter <= 0)
        {
            Utility::Print(CENTRE, "* " + (std::string) Red + ". . ." + ResetColour + " *", LINELENGTH);
            Sleep(500);
            delete QuestionsPtr;
            delete ChoicePtr;
            delete ResponsePtr;
            delete PopulatedChoicePtr;
            delete PopulatedResponsePtr;
            DialogueStatus = false;
            return;
        }

        //Bottom
        Utility::PositionText(0, 12);
        std::cout << "+-----------------------------------------------------------------------+" << std::endl;
        std::cout << Green << " > " << ResetColour << QuestionsPtr->getElement(questionCounter, 0) << std::endl;
        std::cout << "+-----------------------------------------------------------------------+" << std::endl;

        std::cout << Options[0] << " " << currentDialogue->ChoiceText[0] << std::endl;
        std::cout << Options[1] << " " << currentDialogue->ChoiceText[1] << std::endl;
        std::cout << Options[2] << " * " << Red << "Slaps " << dialogueID << ResetColour << " *" << std::endl;
        std::cout << Options[3] << " " << "Goodbye" << std::endl;
        std::cout << "+-----------------------------------------------------------------------+" << std::endl;

        bool selectingKey = true;
        bool selectedChoice = false;

        while (selectingKey == true)
        {
            switch ((_getch())) { //Check value of the last inputed character.
            case KEY_UP:
                TempChoice--;
                if (TempChoice <= 0)
                {
                    TempChoice = 1;
                }
                for (int i = 0; i < 4; i++)
                {
                    if (i + 1 == TempChoice)
                    {
                        Options[i] = Green + (std::string)("[ ") + std::to_string(i + 1) +
                            " ]" + ResetColour;
                    }
                    else
                    {
                        Options[i] = White + (std::string)("[ ") + std::to_string(i + 1) +
                            " ]" + ResetColour;
                    }
                }
                selectingKey = false;
                break;
            case KEY_DOWN:
                TempChoice++;
                if (TempChoice > 4)
                {
                    TempChoice = 1;
                }
                for (int i = 0; i < 4; i++)
                {
                    if (i + 1 == TempChoice)
                    {
                        Options[i] = Green + (std::string)("[ ") + std::to_string(i + 1) +
                            " ]" + ResetColour;
                    }
                    else
                    {
                        Options[i] = White + (std::string)("[ ") + std::to_string(i + 1) +
                            " ]" + ResetColour;
                    }
                }
                selectingKey = false;
                break;
            case KEY_ENTER:
                UserChoice = TempChoice;
                selectedChoice = true;
                selectingKey = false;
                break;
            }
        }

        if (selectingKey == false && selectedChoice == true)
        {
            if (UserChoice == 4) //Back | Goodbye
            {
                //dialogueNumber /= 2;
                //currentDialogue = currentDialogue->PreviousChoice;

                Utility::PositionText(0, 13);
                std::cout << "                                                                      ";
                Utility::PositionText(0, 13);
                std::cout << Green << " > " << ResetColour << "Alright, Goodbye!" << std::endl;
                Sleep(500);
                delete QuestionsPtr;
                delete ChoicePtr;
                delete ResponsePtr;
                delete PopulatedChoicePtr;
                delete PopulatedResponsePtr;
                DialogueStatus = false;
                return;
            }
            else if (UserChoice == 3) //Slap
            {
                AggressionMeter -= Utility::randomNumber(1, 10);
                Utility::PositionText(0, 13);
                std::cout << "                                                                      ";
                Utility::PositionText(0, 13);
                std::cout << Green << " > " << ResetColour << Red << "Ouch! What do you think you're doing?!" << ResetColour << std::endl;
                Sleep(1000);
            }
            else //Foward
            {
                Dialogue* temporaryChoice = currentDialogue;
                if (UserChoice == 1)
                {
                    //std::cout << "You have chosen Option 1: " << currentDialogue->ChoiceText[0] << std::endl;

                    Utility::PositionText(0, 13);
                    std::cout << "                                                                      ";
                    Utility::PositionText(0, 13);
                    std::cout << " > " << ResponsePtr->getElement(dialogueNumber - 1, 0) << std::endl;

                    dialogueNumber *= 2;

                    try { // Block of code to try
                        currentDialogue = new Dialogue(ChoicePtr->getElement(dialogueNumber - 1, 0), ChoicePtr->getElement(dialogueNumber - 1, 1));
                    }
                    catch (...) {
                        // Block of code to handle errors
                        std::cout << "Tree had ended!" << std::endl;
                        if (currentDialogue != nullptr)
                        {
                            delete currentDialogue;
                            currentDialogue = nullptr;
                        }
                        break;

                    }
                    Sleep(3000);
                }
                else
                {
                    //std::cout << "You have chosen Option 2: " << currentDialogue->ChoiceText[1] << std::endl;

                    Utility::PositionText(0, 13);
                    std::cout << "                                                                      ";
                    Utility::PositionText(0, 13);
                    std::cout << " > " << ResponsePtr->getElement(dialogueNumber - 1, 1) << std::endl;

                    dialogueNumber = dialogueNumber * 2 + 1;

                    currentDialogue = new Dialogue(ChoicePtr->getElement(dialogueNumber - 1, 0), ChoicePtr->getElement(dialogueNumber - 1, 1));

                    try { // Block of code to try
                        currentDialogue = new Dialogue(ChoicePtr->getElement(dialogueNumber - 1, 0), ChoicePtr->getElement(dialogueNumber - 1, 1));
                    }
                    catch (...) {
                        // Block of code to handle errors
                        std::cout << "Tree had ended!" << std::endl;
                        if (currentDialogue != nullptr)
                        {
                            delete currentDialogue;
                            currentDialogue = nullptr;
                        }
                        break;
                    }
                    Sleep(1000);
                }
                currentDialogue->PreviousChoice = temporaryChoice;
                questionCounter++;
            }
        }
    }
}

Dialogue::Dialogue(std::string dialogue_ID, std::string Questions_FileString, std::string Responses_FileString)
{
    dialogueID = dialogue_ID;

    questions_FileString = Questions_FileString;
    responses_FileString = Responses_FileString;
}

Dialogue::Dialogue(std::string Input1, std::string Input2)
{
	ChoiceText = new std::string[2];

	ChoiceText[0] = Input1;

	ChoiceText[1] = Input2;
}

Dialogue::~Dialogue()
{
    delete PreviousChoice;
    delete ChoiceText;
    //delete currentDialogue;
}