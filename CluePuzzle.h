#pragma once

#include "Clue.h"
#include "ConclusiveClue.h"
#include "SpecialNPC.h"
#include "Journal.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class CluePuzzle
{
private:
    std::vector<Clue*> gatheredClues;
    std::unordered_map<std::string, ConclusiveClue*> conclusiveClues;

    //Journal
    Journal* currentJournal;
    int currentPage;
public:
    //Puzzle Functions
    void AddClue(Clue* clue);
    void AddConclusiveClue(ConclusiveClue* clue);

    bool CombineResult(Clue* clue1, Clue* clue2);
    bool ConclusionResult(const std::string& conclusiveClueName);

    // Journal Functions
    void PickupJournal();
    void ViewJournal();
    void SearchJournal();

    //Functions
    void setupUI(const std::vector<SpecialNPC>& SpecialNPCs);

    CluePuzzle();
};