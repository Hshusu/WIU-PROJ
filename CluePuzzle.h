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
public:
    std::vector<Clue*> gatheredClues;
    std::unordered_map<std::string, ConclusiveClue*> conclusiveClues;

    //Journal
    Journal* currentJournal;
    int currentPage;

    //Puzzle Functions
    void AddClue(Clue* clue);
    void AddConclusiveClue(ConclusiveClue* clue);

    bool ConclusionResult(const std::string& conclusiveClueName);

    // Journal Functions
    void PickupJournal();
    void UpdateJournal(const std::string& entry);
    void ViewJournal();

    //Functions
    void setupUI(const std::vector<SpecialNPC>& SpecialNPCs);

    CluePuzzle();
};