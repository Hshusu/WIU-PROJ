#pragma once

#include <iostream>
#include <vector>
#include <conio.h> // Include this header for _getch()

class Shop
{
private:
    std::vector<std::string> itemNames;
    std::vector<int> itemQuantities;
    std::vector<int> itemPrices;

public:
    Shop();

    void addItem(const std::string& name, int quantity, int price);

    int getNumItems() const;

    bool buyItem(int index, int quantity);

    int displayItemsAndGetChoice() const;

    int getItemPrice(int index) const;

    const std::string& getItemName(int index) const;
};