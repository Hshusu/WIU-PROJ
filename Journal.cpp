#include "Journal.h"

void Journal::AddEntry(const std::string& entry)
{
    entries.push_back(entry);
}

void Journal::DisplayJournal(int pageNumber) const
{
    system("cls");
    int startIndex = (pageNumber - 1) * entriesPerPage;
    int endIndex = std::min(startIndex + entriesPerPage, static_cast<int>(entries.size()));

    std::cout << "===== Journal - Page " << pageNumber << " =====\n";
    for (int i = startIndex; i < endIndex; ++i) {
        std::cout << "- " << entries[i] << "\n";
    }
    std::cout << "========================\n";
}

void Journal::SearchJournal(const std::string& keyword) const
{
    std::cout << "===== Search Results =====\n";
    for (const std::string& entry : entries) {
        if (entry.find(keyword) != std::string::npos) {
            std::cout << "- " << entry << "\n";
        }
    }
    std::cout << "==========================\n";
}

Journal::Journal(int entriesPerPage)
{
    this->entriesPerPage = entriesPerPage;
}
