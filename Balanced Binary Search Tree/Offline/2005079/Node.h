class Node
{
    int value;
    int height;

public:
    Node *leftChild;
    Node *rightChild;

    Node(int value, Node *leftChild, Node *rightChild)
    {
        this->value = value;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
        this->height = 1;
    }

    ~Node()
    {
        delete leftChild;
        delete rightChild;
    }

    int getValue() { return this->value; }
    void setValue(int value) { this->value = value; }

    int getHeight() { return this->height; }
    void setHeight(int height) { this->height = height; }
};