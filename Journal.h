#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "Utility.h"

class Journal
{
private:
    std::vector<std::string> entries;
    int entriesPerPage;

public:
    void AddEntry(const std::string& entry);
    void DisplayJournal(int pageNumber) const;

    Journal(int entriesPerPage);
};