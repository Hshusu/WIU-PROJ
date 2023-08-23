#include "Node.h"

Node::Node()
{
    Question = "";
    Choice1 = "";
    Response1 = "";
    Choice2 = "";
    Response2 = "";
    nextNode = nullptr;
}

Node::Node(std::string Question, std::string Choice1, std::string Response1, std::string Choice2, std::string Response2)
{
    this->Question = Question;
    this->Choice1 = Choice1;
    this->Response1 = Response1;
    this->Choice2 = Choice2;
    this->Response2 = Response2;
    this->nextNode = nullptr;
}