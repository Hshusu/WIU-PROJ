#include <iostream>
#include <random>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include "location.h"
#include "scene.h"
#include "Entity.h"
#include "Player.h"
#include "Equipment.h"
#include <cwchar>
enum state {
    Explore,
    Action,
    leveup,
    shop,

};

void maxsc()
{
    HWND Hwnd = GetForegroundWindow();
    ShowWindow(Hwnd, SW_MAXIMIZE);
}
void fullsc()
{
    HWND Hwnd = GetForegroundWindow();
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    LONG winstyle = GetWindowLong(Hwnd, GWL_STYLE);
    SetWindowLong(Hwnd, GWL_STYLE, (winstyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    SetWindowPos(Hwnd, HWND_TOP, 0, 0, x, y, 0);

}

int main()
{
    maxsc();
    //fullsc();

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 50;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    //std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    float PMods[6] = { 1,1,1,1,1,1 };
    Player player(PMods, "Marcus");
    int state = Explore;
    scene Map1(1);
    Map1.gridgen();
    Map1.plrgen();
    while (1) {
        if (state == Action) {
            system("cls");

        }
        else if (state == Explore) {
            if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState('A') || GetAsyncKeyState('D') ||
                GetAsyncKeyState('f')) {
                //system("cls");
                Map1.gridgen();
                Map1.plrupdate();
                if (GetAsyncKeyState('S')) {
                    Map1.move(0, 1);
                }
                if (GetAsyncKeyState('W')) {
                    Map1.move(0, -1);
                }
                if (GetAsyncKeyState('A')) {
                    Map1.move(-1, 0);
                }
                if (GetAsyncKeyState('D')) {
                    Map1.move(1, 0);
                }
                Sleep(10);
            }
        }
    }
}