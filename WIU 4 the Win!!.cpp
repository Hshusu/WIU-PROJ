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
enum state {
    Explore,
    Action,
    leveup,
    shop,

};

int main()
{
    float PMods[6] = { 1,1,1,1,1,1 };
    Player* player = new Player(PMods, "Marcus");
    Npc* placeholderE = new Npc("placeholder", 1.1, 10, 1.1, 20);
    int state = Action;
    scene Map1(1);
    Map1.gridgen();

    while (1) {
        if (state == Action) {
            player->statcalc();
            system("cls");
            while ((player->getturn()==false) && (placeholderE->getturn()==false)) {
                //for controlling turn order . value increments up to 100 first to 100 gets turn
                //speed caries over from previous turns of opponent
                if ((player->CrCheck()) || (placeholderE->CrCheck()))
                {
                    break;
                }

            }
            
			if (placeholderE->getturn() == true)//enemies turn
			{
                std::cout << "\033[1;36m> You ran into a FIGHT Grid and bumped into an ENEMY!\033[0m" << std::endl;

                std::cout << "A " << "\033[1;35m" << placeholderE->getname() << "\033[0m" << " approaches you menacingly!" << std::endl;
                std::cout << placeholderE->getname() << "'s \033[1;31m[HP] > \033[0m" << placeholderE->gethp() << std::endl;
                std::cout << "Your \033[1;31m[HP] > \033[0m" << player->gethp() << " " << "\033[1;36m[MANA] > \033[0m" << player->getmana() << std::endl;
                placeholderE->Execute_skill(player, placeholderE->chooseaction());
                placeholderE->setturn(false);

			}
            if(player->getturn()==true){
               
                player->Execute_skill(placeholderE, player->Playerturn(placeholderE));
                player->setturn(false);

            }
            if (placeholderE->gethp() > 0) {
                std::cout<< "enemy killed!";
                state = Explore;

            }
            if (player->gethp() > 0) {
                std::cout << "player killed!";
                state = Explore;

            }
            Sleep(1000);
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