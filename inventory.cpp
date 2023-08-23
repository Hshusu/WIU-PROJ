#include "inventory.h"
#include <vector>
#include<iostream>
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
inventory::inventory(int x, int y) {
    pointer.X = 0;
    pointer.Y = 0;

    for (int i = 0; i < y; i++) {
        // Vector to store column elements
        std::vector<int> v1;

        for (int j = 0; j < x; j++) {
            v1.push_back(-1);

        }

        // Pushing back above 1D vector
        // to create the 2D vector
        InventoryVector.push_back(v1);
    }

}
void inventory::Move(const int x, const int y, Item current) {
    pointer.Y = (pointer.Y + y);
    if (pointer.Y < 0) {
        pointer.Y = 0;
    }
    if (pointer.Y >= InventoryVector.size() - 1 - current.getHeight()) {
        pointer.Y = InventoryVector.size() - 1 - current.getHeight();
    }
    pointer.X = (pointer.X + x);
    if (pointer.X < 0) {
        pointer.X = 0;
    }
    if (pointer.X >= InventoryVector[0].size() - 1 - current.getWidth()) {
        pointer.X = InventoryVector[0].size() - 1 - current.getWidth();
    }
}
void inventory::RenderInventory(Item current)
{
    for (int i = 0; i < InventoryVector.size(); i++)
    {

        for (int j = 0; j < InventoryVector[0].size(); j++) {

            if (((i - pointer.Y) <= current.getHeight()) && ((j - pointer.X) <= current.getWidth()) && (i >= pointer.Y) && (j >= pointer.X)) {
                SetConsoleTextAttribute(h, 1);
                if (InventoryVector[i][j] != -1) {
                    SetConsoleTextAttribute(h, 4);
                }
            }
            else {
                SetConsoleTextAttribute(h, 15);
            }


            COORD zone1_Coords = { j * 5,i * 3 };
            SetConsoleCursorPosition(h, zone1_Coords);
            std::cout << "-----";

            COORD zone2_Coords = { j * 5,i * 3 + 1 };
            SetConsoleCursorPosition(h, zone2_Coords);
            std::cout << "|";
            if (InventoryVector[i][j] == -1)
            {
                std::cout << "   ";

            }
            else if (InventoryVector[i][j] != -1)
            {
                SetConsoleTextAttribute(h, InventoryVector[i][j] + 1);
                std::cout << " X ";
                SetConsoleTextAttribute(h, 15);
            }
            if (((i - pointer.Y) <= current.getHeight()) && ((j - pointer.X) <= current.getWidth()) && (i >= pointer.Y) && (j >= pointer.X)) {
                SetConsoleTextAttribute(h, 1);
                if (InventoryVector[i][j] != -1) {
                    SetConsoleTextAttribute(h, 4);
                }
            }
            else {
                SetConsoleTextAttribute(h, 15);
            }
            std::cout << "|";
            COORD zone3_Coords = { j * 5,i * 3 + 2 };
            SetConsoleCursorPosition(h, zone3_Coords);
            std::cout << "-----";

        }

    }
}
void inventory::RenderInventory()
{
    for (int i = 0; i < InventoryVector.size(); i++)
    {

        for (int j = 0; j < InventoryVector[0].size(); j++) {

            SetConsoleTextAttribute(h, 15);


            COORD zone1_Coords = { j * 5,i * 3 };
            SetConsoleCursorPosition(h, zone1_Coords);
            std::cout << "-----";

            COORD zone2_Coords = { j * 5,i * 3 + 1 };
            SetConsoleCursorPosition(h, zone2_Coords);
            std::cout << "|";
            if (InventoryVector[i][j] == -1)
            {
                std::cout << "   ";

            }
            else if (InventoryVector[i][j] != -1)
            {
                SetConsoleTextAttribute(h, InventoryVector[i][j] + 1);
                std::cout << " X ";
                SetConsoleTextAttribute(h, 15);
            }
            SetConsoleTextAttribute(h, 15);
            std::cout << "|";
            COORD zone3_Coords = { j * 5,i * 3 + 2 };
            SetConsoleCursorPosition(h, zone3_Coords);
            std::cout << "-----";

        }

    }
}
bool inventory::placeitem(Item current)
{
    for (int i = 0; i < InventoryVector.size(); i++)
    {

        for (int j = 0; j < InventoryVector[0].size(); j++) {

            if (((i - pointer.Y) <= current.getHeight()) && ((j - pointer.X) <= current.getWidth()) && (i >= pointer.Y) && (j >= pointer.X)) {
                if (InventoryVector[i][j] != -1) {
                    return false;
                }
            }
        }
    }
    for (int i = 0; i < InventoryVector.size(); i++)
    {

        for (int j = 0; j < InventoryVector[0].size(); j++) {

            if (((i - pointer.Y) <= current.getHeight()) && ((j - pointer.X) <= current.getWidth()) && (i >= pointer.Y) && (j >= pointer.X)) {
                InventoryVector[i][j] = current.getID();
            }
        }
    }
    return true;
}

void inventory::movescroll(int x)
{
    scroll = scroll - x;
    if (scroll > 0) {
        scroll = 0;
    }
    if (scroll < -scrollmax) {
        scroll = -scrollmax;
    }
}
void inventory::setscroll(int x)
{
    scroll = scroll = x;

}

int inventory::getscroll()
{
    return scroll;
}

void inventory::setmaxscroll(int x)
{
    scrollmax = x;
}

int inventory::getmaxscroll()
{
    return scrollmax;
}

int inventory::discard(int x)
{
    for (int i = 0; i < InventoryVector.size(); i++)
    {

        for (int j = 0; j < InventoryVector[0].size(); j++) {
            if (InventoryVector[i][j] == x) {
                InventoryVector[i][j] = -1;

            }
        }
    }
    if ((-scroll >= 0) && (-scroll != 999)) {
        return -scroll;
    }
    else {
        return -999;
    }
}
