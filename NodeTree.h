#pragma once
#include "Node.h"
#include <iostream>
#include <string>

class NodeTree
{
public:
    Node* Head;
    Node* nexttest;
    
    std::string tempQuestion;
    std::string tempChoice1;
    std::string tempResponse1;
    std::string tempChoice2;
    std::string tempResponse2;
    
    int insertCounter;
    int dialogueCounter;

    bool DialogueStatus;

    void insertNode(std::string Question, std::string Choice1, std::string Response1, std::string Choice2, std::string Response2);
    void deleteNode(int nodePosition);
    void printList(void);

    bool getDialogueStatus(void) const;
    void setDialogueStatus(bool dS);

    NodeTree();
};