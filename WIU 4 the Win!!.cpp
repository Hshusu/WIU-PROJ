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

#include "Npc.h"

#include <cwchar>

enum state {
    Explore,
    Action,
    leveup,
    shop,

};

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
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
bool crParty(Player* player[4]) {
    for (int i = 0; i < 4; i++) {
        if (player[i] != nullptr) {

            if (player[i]->CrCheck())
            {
                return true;

            }
        }
    }
    return false;
}
int main()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD scrn;
    maxsc();
    //fullsc();

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 20;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    //std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    const int max_Psize = 4;
    float PMods[6] = { 1,1,1,1,1,1 };
    bool sceneloaded = false;
    Player* player[max_Psize] = { nullptr };
    player[0] = new Player(PMods, "Marcus", Lightning, Ice);
    player[1]= new Player("Remus", 1.1, 10, 1.3, 20, Fire, Darkness);
    Npc* placeholderE = new Npc("placeholder", 2, 10, 1.1, 20,Fire,Darkness);
    int state = Action;
    scene Map1(1);

    while (1) {
        if (state == Action) {
            player[0]->statcalc();
            system("cls");
            while (1) {
                //for controlling turn order . value increments up to 100 first to 100 gets turn
                //speed caries over from previous turns of opponent
                if (placeholderE->CrCheck()) {
                    break;
                }

                if (crParty(player)) {
                    break;
                }
            }
			if (placeholderE->getturn() == true)//enemies turn
			{
                player[0]->Uigen(*placeholderE);
                placeholderE->Execute_skill(player[0], placeholderE->chooseaction());
                placeholderE->setturn(false);

			}
            for (int i = 0; i < max_Psize; i++) {
                if (player[i] != nullptr) {
                    if (player[i]->getturn() == true) {

                        player[i]->Execute_skill(placeholderE, player[i]->Playerturn(placeholderE));
                        player[i]->setturn(false);
                        break;

                    }
                }
            }
            if (placeholderE->gethp() <= 0) {
                std::cout<< "enemy killed!";
                state = Explore;

            }
            for (int i = 0; i < max_Psize; i++) {
                if (player[i] != nullptr) {
                    if (player[i]->gethp() <= 0) {
                        std::cout <<player[i]->getname()<<" killed!";
                        state = Explore;
                        break;

                    }
                }
            }

            Sleep(2000);
            system("cls");

        }
        else if (state == Explore) {
            if (sceneloaded == false) {
                Map1.gridgen();
                Map1.plrupdate();
                sceneloaded = true;
            }
            if (GetAsyncKeyState('F')) {
                Map1.gridgen();
            }
            if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState('A') || GetAsyncKeyState('D')) {
                system("cls");
                ShowConsoleCursor(false);
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
                
            }
            if (GetAsyncKeyState('X'))
            {
                /*scene Map1(2);
                system("cls");
                Map1.gridgen();
                Map1.plrgen();*/

                Map1.checkNPC();
            }
        }
    }
}