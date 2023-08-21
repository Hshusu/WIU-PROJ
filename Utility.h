#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <cwchar>
#include <random>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'

//Foreground (Text) Colors:
#define Black "\033[0;30m"
#define Red "\033[0;31m"
#define Green "\033[0;32m"
#define Yellow "\033[0;33m"
#define Blue "\033[0;34m"
#define Magenta "\033[0;35m"
#define Cyan "\033[0;36m"
#define White "\033[0;37m"

//Bright (Bold) Foreground Colors:
#define BrightBlack "\033[1;30m"
#define BrightRed "\033[1;31m"
#define BrightGreen "\033[1;32m"
#define BrightYellow "\033[1;33m"
#define BrightBlue "\033[1;34m"
#define BrightMagenta "\033[1;35m"
#define BrightCyan "\033[1;36m"
#define BrightWhite "\033[1;37m"

//Background Colors:
#define BlackBackground "\033[40m"
#define RedBackground "\033[41m"
#define GreenBackground "\033[42m"
#define YellowBackground "\033[43m"
#define BlueBackground "\033[44m"
#define MagentaBackground "\033[45m"
#define CyanBackground "\033[46m"
#define WhiteBackground "\033[47m"

#define ResetColour "\033[0m"
enum Position { LEFT, CENTRE, RIGHT };
static HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE); 

namespace Utility
{   
    /* Function that generates a Random Number */
    int randomNumber(int minNum, int maxNum);

    /* Function that forces the User's screen to be FullScreen on Start */
    void MaxScreen();

    /* Function that changes the Console font size */
    void SetupFont(int fontSize);

    /* Function Positions text based on coordinates given */
    void PositionText(int x, int y);

    /* Function that prints Text either in Left, Center or Right of Screen. */
    /* Print(LEFT, "Left", LINELENGTH) */
    /* Print(RIGHT, "Right", LINELENGTH) */
    /* Print(CENTRE, "Centre", LINELENGTH) */
    void Print(Position pos, std::string s, int linelength);

    void ShowConsoleCursor(bool showFlag);
};