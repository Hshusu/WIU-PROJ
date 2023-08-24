#include "Journal.h"

void Journal::AddEntry(const std::string& entry)
{
    entries.push_back(entry);
}

void Journal::DisplayJournal(int pageNumber) const
{
    system("cls"); // Clear the screen
    Utility::SetupFont(30);
    Utility::PositionText(0, 1);
    Utility::Print(CENTRE, "+==================================================>< Clue Journal ><==================================================+", 120);
    Utility::PositionText(0, 3);
    std::cout << "========================================================================================================================";
    Utility::PositionText(0, 5);
    for (size_t i = 0; i < entries.size(); ++i) {
        std::cout << "- " << entries[i] << "\n" << "\n";
    }
    std::cout << "========================================================================================================================" << std::endl;
    std::cout << "Press 'M' to close...";
    char input;
    do {
        input = _getch(); // Get a single character input
    } while (input != 'M' && input != 'm');

    system("cls"); // Clear the screen again
}

Journal::Journal(int entriesPerPage)
{
    this->entriesPerPage = entriesPerPage;
}
