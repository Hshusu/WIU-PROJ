#include "CluePuzzle.h"

void CluePuzzle::AddClue(Clue* clue)
{
    gatheredClues.push_back(clue);
}

void CluePuzzle::AddConclusiveClue(ConclusiveClue* clue)
{
    conclusiveClues[clue->getName()] = clue;
}

bool CluePuzzle::CombineResult(Clue* clue1, Clue* clue2)
{
    // Implement more complex logic to combine clues
    // Here, we'll simulate a deduction process for illustrative purposes
    if (clue1->getType() == ClueType::Physical && clue2->getType() == ClueType::Testimonial) {
        std::cout << "Combining " << clue1->getName() << " and " << clue2->getName() << "...\n";
        std::cout << "Deduction: The physical evidence supports the witness testimony.\n";
        return true;  // Deduction successful
    }
    else if (clue1->getType() == ClueType::Testimonial && clue2->getType() == ClueType::Physical) {
        std::cout << "Combining " << clue1->getName() << " and " << clue2->getName() << "...\n";
        std::cout << "Deduction: The witness testimony corroborates the physical evidence.\n";
        return true;  // Deduction successful
    }

    std::cout << "The clues don't seem to lead to a deduction.\n";
    return false;  // Deduction failed
}

bool CluePuzzle::ConclusionResult(const std::string& conclusiveClueName)
{
    auto it = conclusiveClues.find(conclusiveClueName);
    if (it != conclusiveClues.end()) {
        std::cout << "Congratulations! You've solved the puzzle. Conclusion: " << it->second->getDescription() << std::endl;
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