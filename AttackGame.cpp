#include "AttackGame.h"
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
    cout << "====================V===================";

    for (int i = 0; i < row; i++) 
    {
        SetCursorPosition(gameOffsetX, gameOffsetY + i);

        for (int j = 0; j < col; j++)
        {
            mapData[i][j] = '.';
            std::cout << mapData[i][j];
        }
    }
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
                            //Change color and change previous position
                            SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //White
                            SetCursorPosition(gameOffsetX + barXpos, gameOffsetY + barYpos);
                            cout << '.';
                        }
                        else
                        {
                            SetCursorPosition(1, 15);
                            barMovingLeft = false;
                            cout << barMovingLeft;
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
                            //Change color and change previous position
                            SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //White
                            SetCursorPosition(gameOffsetX + barXpos, gameOffsetY + barYpos);
                            cout << '.';
                        }
                        else
                        {
                            SetCursorPosition(1, 15);
                            barMovingLeft = true;
                            cout << barMovingLeft;
                        }
                    }
                }
            }
        }
    }
}

void AttackGame :: CheckMapData()
{
    for (int i = 0; i < row; i++)
    {
        SetCursorPosition(gameOffsetX, gameOffsetY + i);

        for (int j = 0; j < col; j++)
        {
            std::cout << mapData[i][j];
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

AttackGame::AttackGame(void)
{
    DrawAttackStart();
    DrawBar();

    while (!Stop)
    {
        CheckInput();

        MoveBarLeft();

        MoveBarRight();

        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }

    SetCursorPosition(0, 0);
}