#include "Shop.h"

Shop::Shop()
{
}

void Shop::addItem(const std::string& name, int quantity, int price)
{
    itemNames.push_back(name);
    itemQuantities.push_back(quantity);
    itemPrices.push_back(price);
}

int Shop::getNumItems() const
{
    return itemNames.size();
}

bool Shop::buyItem(int index, int quantity)
{
    if (index >= 0 && index < itemNames.size() && quantity > 0 && quantity <= itemQuantities[index]) {
        itemQuantities[index] -= quantity;
        return true;
    }
    return false;
}

int Shop::displayItemsAndGetChoice() const
{
    int selectedOption = 0;
    char keyPressed;

    do {
        system("cls"); // Clear the console (Windows-specific)
        std::cout << "Welcome to the Shop!\n";

        for (int i = 0; i < itemNames.size(); ++i) {
            if (i == selectedOption) {
                std::cout << "> ";
            }
            else {
                std::cout << "  ";
            }
            std::cout << itemNames[i] << " (" << itemQuantities[i] << " left) - $" << itemPrices[i] << "\n";
        }

        keyPressed = _getch(); // Get a key press
        if (keyPressed == 72) { // Up arrow key
            if (selectedOption > 0) {
                selectedOption--;
            }
        }
        else if (keyPressed == 80) { // Down arrow key
            if (selectedOption < itemNames.size() - 1) {
                selectedOption++;
            }
        }
    } while (keyPressed != 13); // Enter key

    return selectedOption;
}

int Shop::getItemPrice(int index) const
{
    if (index >= 0 && index < itemPrices.size()) {
        return itemPrices[index];
    }
    return 0; // Or some default value
}

const std::string& Shop::getItemName(int index) const
{
    static std::string emptyString; // Return an empty string if index is out of bounds
    if (index >= 0 && index < itemNames.size()) {
        return itemNames[index];
    }
    return emptyString;
}
