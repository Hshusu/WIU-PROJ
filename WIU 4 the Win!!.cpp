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
enum state {
    Explore,
    Action,
    leveup,
    shop,

};

int main()
{
    float PMods[6] = { 1,1,1,1,1,1 };
    Player player(PMods, "Marcus");
    int state = Action;
    scene Map1(1);
    Map1.gridgen();

    while (1) {
        if (state == Action) {
            system("cls");

        }
        else if (state == Explore) {
            if (GetAsyncKeyState('W') || GetAsyncKeyState('S') || GetAsyncKeyState('A') || GetAsyncKeyState('D') ||
                GetAsyncKeyState('f')) {
                system("cls");
                Map1.gridgen();
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
                Sleep(1);
            }
        }
    }
}