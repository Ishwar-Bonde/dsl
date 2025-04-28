#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Node
{
public:
    string name;
    vector<Node *> children;
    Node(string nodeName) : name(nodeName) {}
    void addChild(Node *childNode)
    {
        children.push_back(childNode);
    }
    void printNode(int level = 0)
    {
        for (int i = 0; i < level; ++i)
        {
            cout << " ";
        }
        cout << name << endl;
        for (Node *child : children)
        {
            child->printNode(level + 1);
        }
    }
};
int main()
{
    Node *book = new Node("Book");
    Node *chapter1 = new Node("Chapter 1");
    Node *chapter2 = new Node("Chapter 2");
    Node *section_1 = new Node("Section 1.1");
    Node *section_2 = new Node("Section 1.2");
    Node *section_3 = new Node("Section 2.1");
    Node *subsection_1_1 = new Node("SubSection 1.1.1");
    Node *subsection_1_2 = new Node("SubSection 1.1.2");
    section_1->addChild(subsection_1_1);
    section_1->addChild(subsection_1_2);
    chapter1->addChild(section_1);
    chapter1->addChild(section_2);
    chapter2->addChild(section_3);

    book->addChild(chapter1);
    book->addChild(chapter2);
    book->printNode();
    delete book;
    delete chapter1;
    delete chapter2;
    delete section_1;
    delete section_2;
    delete section_3;
    delete subsection_1_1;
    delete subsection_1_2;
    return 0;
}