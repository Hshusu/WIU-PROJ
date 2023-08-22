#include "AttackGame.h"
#include "Player.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <windows.h>

using namespace std;

void AttackGame::SetConsoleTextColor(int colorCode)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, colorCode);
}

void AttackGame::SetCursorPosition(int x, int y)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD cursorpos;
    cursorpos.X = x;
    cursorpos.Y = y;

    SetConsoleCursorPosition(consoleHandle, cursorpos);
}

void AttackGame::OverlayScreen()
{
    SetCursorPosition(gameOffsetX, gameOffsetY);
}

void AttackGame::DrawAttackStart()
{ 
    SetCursorPosition(gameOffsetX, gameOffsetY - 1);
    SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "========================================";

    for (int i = 0; i < row; i++) 
    {
        SetCursorPosition(gameOffsetX, gameOffsetY + i);

        for (int j = 0; j < col; j++)
        {
            mapData[i][j] = '.';

            if (j == 16 || j == 17 || j == 18 || j == 21 || j == 22 || j == 23)
            {
                SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); //Yellow
            }
            else if (j == 19 || j == 20)
            {
                SetConsoleTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); //Green
            }
            else
            {
                SetConsoleTextColor(0); //Black
            }

            cout << mapData[i][j];
        }
    }

    SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    SetCursorPosition(gameOffsetX, gameOffsetY + 9);
    cout << "========================================";
    SetConsoleTextColor(0); //Black
}

void AttackGame :: DrawBar()
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (j == col - 1)
            {
                mapData[i][j] = '|'; // Vertical column character
                SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY); // Change colour
                SetCursorPosition(gameOffsetX + j, gameOffsetY + i);
                cout << '|';
            }
            else
            {
                
                mapData[i][j] = '.';
            }
        }
        cout << endl;
    }
}

void AttackGame :: MoveBarLeft()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            //check if I and J remains within bounds
            if (i >= 0 && i < row && j >= 0 && j < col)
            {
                //Find all bar char in 2d array
                if (mapData[i][j] == '|')
                {
                    barXpos = j;
                    barYpos = i;

                    if (barMovingLeft)
                    {
                        if (barXpos > 0)
                        {
                            //Store data of bar location in 2d array
                            mapData[barYpos][barXpos - 1] = '|';
                            mapData[barYpos][barXpos] = '.';

                            //Display Bar and empty spaces over 2d array map data
                            SetCursorPosition(gameOffsetX + barXpos - 1, gameOffsetY + barYpos);
                            //Change color and Display bar
                            SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY); //Red
                            cout << '|';

                            if (j == 16 || j == 17 || j == 18 || j == 21 || j == 22 || j == 23)
                            {
                                SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); //Yellow
                            }
                            else if (j == 19 || j == 20)
                            {
                                SetConsoleTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); //Green
                            }
                            else
                            {
                                SetConsoleTextColor(0); //Black
                            }
                            
                            SetCursorPosition(gameOffsetX + barXpos, gameOffsetY + barYpos);
                            cout << '.';
                        }
                        else
                        {
                            barMovingLeft = false;
                        }
                    }
                }
            }
        }
    }
}

void AttackGame :: MoveBarRight()
{
    OverlayScreen();

    for (int i = row; i >= 0; i--)
    {
        for (int j = col; j >= 0; j--)
        {
            //check if I and J remains within bounds
            if (i >= 0 && i < row && j >= 0 && j < col)
            {
                //Find all bar char in 2d array
                if (mapData[i][j] == '|')
                {
                    barXpos = j;
                    barYpos = i;

                    if (!barMovingLeft)
                    {
                        if (barXpos < col - 1)
                        {
                            //Store data of bar location in 2d array
                            mapData[barYpos][barXpos + 1] = '|';
                            mapData[barYpos][barXpos] = '.';

                            //Display Bar and empty spaces over 2d array map data
                            SetCursorPosition(gameOffsetX + barXpos + 1, gameOffsetY + barYpos);
                            //Change color and Display bar
                            SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY); //Red
                            cout << '|';

                            if (j == 16 || j == 17 || j == 18 || j == 21 || j == 22 || j == 23)
                            {
                                SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); //Yellow
                            }
                            else if (j == 19 || j == 20)
                            {
                                SetConsoleTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); //Green
                            }
                            else
                            {
                                SetConsoleTextColor(0); //Black
                            }

                            SetCursorPosition(gameOffsetX + barXpos, gameOffsetY + barYpos);
                            cout << '.';
                        }
                        else
                        {
                            barMovingLeft = true;
                        }
                    }
                }
            }
        }
    }
}

void AttackGame :: CheckMapData()
{
    if (barMovingLeft == true)
    {
        for (int i = 0; i < row; i++)
        {
            SetCursorPosition(gameOffsetX, gameOffsetY + i);

            for (int j = 0; j < col; j++)
            {
                if (mapData[0][16] == '|' || mapData[0][17] == '|' || mapData[0][18] == '|' ||
                    mapData[0][21] == '|' || mapData[0][22] == '|' || mapData[0][23] == '|')
                {
                    SetdmgModifier(1.2f);
                }
                else if (mapData[0][19] == '|' || mapData[0][20] == '|')
                {
                    SetdmgModifier(1.5f);
                }
                else
                {
                    SetdmgModifier(1.0f);
                }
            }
        }
    }
    else
    {
        for (int i = row; i >= 0; i--)
        {
            for (int j = col; j >= 0; j--)
            {
                SetCursorPosition(gameOffsetX, gameOffsetY + i);

                for (int j = 0; j < col; j++)
                {
                    if (mapData[0][16] == '|' || mapData[0][17] == '|' || mapData[0][18] == '|' ||
                        mapData[0][21] == '|' || mapData[0][22] == '|' || mapData[0][23] == '|')
                    {
                        SetdmgModifier(1.2f);
                    }
                    else if (mapData[0][19] == '|' || mapData[0][20] == '|')
                    {
                        SetdmgModifier(1.5f);
                    }
                    else
                    {
                        SetdmgModifier(1.0f);
                    }
                }
            }
        }
    }
}

void AttackGame :: CheckInput()
{
    if (GetAsyncKeyState(VK_SPACE))
    {
        Stop = true;
        CheckMapData();
    }
}

void AttackGame::SetdmgModifier(float mod)
{
    dmgModifier = mod;
}

float AttackGame::GetdmgModifier(void)
{
    return dmgModifier;
}

AttackGame::AttackGame(void)
{
    DrawAttackStart();
    DrawBar();

    while (!Stop)
    {

        MoveBarLeft();

        MoveBarRight();

        CheckInput();

        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }

    SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetCursorPosition(0, 19);
}