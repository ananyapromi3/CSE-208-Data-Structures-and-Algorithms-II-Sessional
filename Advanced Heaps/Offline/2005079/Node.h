#include <iostream>

class Node
{
    int value;
    int degree;
    int level;

public:
    Node *child;
    Node *sibling;
    Node *parent;

    Node(int value)
    {
        this->value = value;
        this->child = NULL;
        this->sibling = NULL;
        this->parent = NULL;
        this->degree = 0;
        this->level = 0;
    }

    ~Node()
    {
        delete child;
        delete sibling;
        delete parent;
    }

    int getValue() { return this->value; }
    void setValue(int value) { this->value = value; }

    int getDegree() { return this->degree; }
    void setDegree(int degree) { this->degree = degree; }

    int getLevel() { return this->level; }
    void setLevel(int level) { this->level = level; }
};