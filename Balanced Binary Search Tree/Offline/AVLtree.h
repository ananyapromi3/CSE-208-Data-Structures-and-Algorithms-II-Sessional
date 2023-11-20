#include <iostream>
#include "Node.h"
using namespace std;

class BST
{
    Node *root;

    void display(Node *node)
    {
        if (node)
        {
            cout << node->getValue();
        }
        if (node->leftChild || node->rightChild)
        {
            cout << "(";
            if (node->leftChild)
            {
                display(node->leftChild);
            }
            cout << ",";
            if (node->rightChild)
            {
                display(node->rightChild);
            }
            cout << ")";
        }
    }

    void inorder(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        inorder(node->leftChild);
        cout << node->getValue() << " ";
        inorder(node->rightChild);
    }

    Node *insert(Node *node, int value)
    {
        if (!node)
        {
            return new Node(value, NULL, NULL);
        }
        if (value < node->getValue())
        {
            node->leftChild = insert(node->leftChild, value);
        }
        else if (value > node->getValue())
        {
            node->rightChild = insert(node->rightChild, value);
        }
        node->setHeight(max(height(node->leftChild), height(node->rightChild)) + 1);
        int dif = imbalance(node);
        if (dif > 1)
        {
            if (node->leftChild->getValue() < value)
            {
                node->leftChild = leftRotate(node->leftChild);
            }
            return rightRotate(node);
        }
        if (dif < -1)
        {
            if (node->rightChild->getValue() > value)
            {
                node->rightChild = rightRotate(node->rightChild);
            }
            return leftRotate(node);
        }
        return node;
    }

    Node *rightRotate(Node *node)
    {
        Node *l = node->leftChild;
        Node *lr = l->rightChild;
        l->rightChild = node;
        node->leftChild = lr;
        node->setHeight(max(height(node->leftChild), height(node->rightChild)) + 1);
        l->setHeight(max(height(l->leftChild), height(l->rightChild)) + 1);
        return l;
    }
    Node *leftRotate(Node *node)
    {
        Node *r = node->rightChild;
        Node *rl = r->leftChild;
        r->leftChild = node;
        node->rightChild = rl;
        node->setHeight(max(height(node->leftChild), height(node->rightChild)) + 1);
        r->setHeight(max(height(r->leftChild), height(r->rightChild)) + 1);
        return r;
    }

    int height(Node *node)
    {
        if (!node)
        {
            return 0;
        }
        return node->getHeight();
    }

    int imbalance(Node *node)
    {
        if (!node)
        {
            return 0;
        }
        return height(node->leftChild) - height(node->rightChild);
    }

    Node *minVal(Node *node)
    {
        Node *temp = node;
        while (temp->leftChild)
        {
            temp = temp->leftChild;
        }
        return temp;
    }

    Node *deleteNode(Node *node, int value)
    {
        if (!node)
        {
            return node;
        }
        if (value < node->getValue())
        {
            node->leftChild = deleteNode(node->leftChild, value);
        }
        else if (value > node->getValue())
        {
            node->rightChild = deleteNode(node->rightChild, value);
        }
        else
        {
            if (!node->leftChild && !node->rightChild)
            {
                Node *temp = node;
                node = NULL;
                delete temp;
            }
            else if (!node->rightChild)
            {
                Node *temp = node->leftChild;
                *node = *temp;
                delete temp;
            }
            else if (!node->leftChild)
            {
                Node *temp = node->rightChild;
                *node = *temp;
                delete temp;
            }
            else
            {
                Node *temp = minVal(node->rightChild);
                node->setValue(temp->getValue());
                node->rightChild = deleteNode(node->rightChild, temp->getValue());
            }
        }
        if (!node)
        {
            return node;
        }
        node->setHeight(max(height(node->leftChild), height(node->rightChild)) + 1);
        int dif = imbalance(node);
        if (dif > 1)
        {
            if (imbalance(node->leftChild) < 0)
            {
                node->leftChild = leftRotate(node->leftChild);
            }
            return rightRotate(node);
        }
        if (dif < -1)
        {
            if (imbalance(node->rightChild) > 0)
            {
                node->rightChild = rightRotate(node->rightChild);
            }
            return leftRotate(node);
        }
        return node;
    }

public:
    BST()
    {
        root = NULL;
    }

    ~BST()
    {
        delete root;
    }

    void displayBST()
    {
        if (!this->root)
        {
            cout << "\n";
            return;
        }
        display(this->root);
        cout << "\n";
    }

    void insertVal(int value)
    {
        root = insert(root, value);
    }

    bool find(int value)
    {
        if (!this->root)
        {
            return false;
        }
        Node *temp;
        temp = root;
        while (true)
        {
            if (value < temp->getValue())
            {
                if (!temp->leftChild)
                {
                    return false;
                }
                temp = temp->leftChild;
            }
            else if (value > temp->getValue())
            {
                if (!temp->rightChild)
                {
                    return false;
                }
                temp = temp->rightChild;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    void deleteVal(int key)
    {
        root = deleteNode(root, key);
    }

    void inorderTraversal()
    {
        if (!this->root)
        {
            return;
        }
        inorder(this->root);
        cout << "\n";
    }
};