#include "CluePuzzle.h"

void CluePuzzle::AddClue(Clue* clue)
{
    gatheredClues.push_back(clue);
}

void CluePuzzle::AddConclusiveClue(ConclusiveClue* clue)
{
    conclusiveClues[clue->getName()] = clue;
}

bool CluePuzzle::ConclusionResult(const std::string& conclusiveClueName)
{
    auto it = conclusiveClues.find(conclusiveClueName);
    if (it != conclusiveClues.end()) {
        std::cout << "Congratulations! You've solved the case. Conclusion: " << it->second->getDescription() << std::endl;
        return true;
    }
    else {
        std::cout << "The clues don't seem to lead to a conclusive conclusion." << std::endl;
        return false;
    }
}

//Journal Functions
void CluePuzzle::PickupJournal()
{
    Journal* newJournal = new Journal(5); // 5 Entries per page
    currentJournal = newJournal;
    currentPage = 1;
}

void CluePuzzle::UpdateJournal(const std::string& entry)
{
    currentJournal->AddEntry(entry);
}

void CluePuzzle::ViewJournal()
{
    currentJournal->DisplayJournal(1);
}

void CluePuzzle::setupUI(const std::vector<SpecialNPC>& SpecialNPCs)
{
}

CluePuzzle::CluePuzzle()
{
    PickupJournal();
}