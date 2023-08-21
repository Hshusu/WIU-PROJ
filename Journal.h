#pragma once
#include <iostream>
#include <string>
#include <vector>

class Journal
{
private:
    std::vector<std::string> entries;
    int entriesPerPage;

public:
    void AddEntry(const std::string& entry);
    void DisplayJournal(int pageNumber) const;
    void SearchJournal(const std::string& keyword) const;

    Journal(int entriesPerPage);
};