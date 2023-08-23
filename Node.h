#pragma once
#include <string>

class Node
{
public:
    std::string Question;
    std::string Choice1, Response1;
    std::string Choice2, Response2;
    Node* nextNode;

    Node();
    Node(std::string Question, std::string Choice1, std::string Response1, std::string Choice2, std::string Response2);
};