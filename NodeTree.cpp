#include "NodeTree.h"

void NodeTree::insertNode(std::string Question, std::string Choice1, std::string Response1, std::string Choice2, std::string Response2)
{
    // Create the new Node.
    Node* newNode = new Node(Question, Choice1, Response1, Choice2, Response2);

    // Assign to Head
    if (Head == nullptr) {
        Head = newNode;
        return;
    }

    // Traverse till end of list
    Node* temp = Head;
    while (temp->nextNode != nullptr) {

        // Update temp
        temp = temp->nextNode;
    }

    // Insert at the last.
    temp->nextNode = newNode;

    insertCounter++;
}

void NodeTree::deleteNode(int nodeOffset)
{
    //Node* temp1 = Head, * temp2 = NULL;
    //int ListLen = 0;

    //if (Head == NULL) {
    //    std::cout << "List empty." << std::endl;
    //    return;
    //}

    //// Find length of the linked-list.
    //while (temp1 != NULL) {
    //    temp1 = temp1->nextNode;
    //    ListLen++;
    //}

    //// Check if the position to be
    //// deleted is greater than the length
    //// of the linked list.
    //if (ListLen < nodeOffset) {
    //    std::cout << "Index out of range"
    //        << std::endl;
    //    return;
    //}

    //// Declare temp1
    //temp1 = Head;

    //// Deleting the newNode.
    //if (nodeOffset == 1) {

    //    // Update newNode
    //    Head = Head->nextNode;
    //    delete temp1;
    //    return;
    //}

    //// Traverse the list to
    //// find the node to be deleted.
    //while (nodeOffset-- > 1) {

    //    // Update temp2
    //    temp2 = temp1;

    //    // Update temp1
    //    temp1 = temp1->nextNode;
    //}

    //// Change the nextNode pointer
    //// of the previous node.
    //temp2->nextNode = temp1->nextNode;

    //// Delete the node
    //delete temp1;
}

void NodeTree::printList()
{
    /*if (Head == nullptr)
    {
        system("cls");
        std::cout << "List empty" << std::endl;
        return false;
    }*/

    // Traverse the list.
    if (nexttest != nullptr) {
        tempQuestion = nexttest->Question;
        tempChoice1 = nexttest->Choice1;
        tempResponse1 = nexttest->Response1;
        tempChoice2 = nexttest->Choice2;
        tempResponse2 = nexttest->Response2;
        nexttest = nexttest->nextNode;
    }
    else
    {
        if (dialogueCounter > insertCounter)
        {
            DialogueStatus = false;
            return;
        }
        else
        {
            nexttest = Head;
            tempQuestion = nexttest->Question;
            tempChoice1 = nexttest->Choice1;
            tempResponse1 = nexttest->Response1;
            tempChoice2 = nexttest->Choice2;
            tempResponse2 = nexttest->Response2;
            nexttest = nexttest->nextNode;
        }
    }

    dialogueCounter++;
}

bool NodeTree::getDialogueStatus(void) const
{
    return DialogueStatus;
}

void NodeTree::setDialogueStatus(bool dS)
{
    DialogueStatus = dS;
}

NodeTree::NodeTree()
{
    Head = nullptr;
    DialogueStatus = true;
    tempQuestion = "";
    tempChoice1 = "";
    tempResponse1 = "";
    tempChoice2 = "";
    tempResponse2 = "";
}