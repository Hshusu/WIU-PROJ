#pragma once
#include <iostream>
#include <string>
#include <windows.h>

class Item {
private:
    std::string Name;
    COORD pos;
    int ID;
    int width;
    int height;
    bool placed = false;
public:
    Item(int height, int width, std::string Name, int ID);
    std::string getName(void);
    int getWidth(void);
    int getID();
    int getHeight(void);
    void setName(std::string Name);
    void setheight(int height);
    void setwidth(int width);
    void setpos(int x, int y);
    void rotate();
    void place();

    bool getplaced();


};

