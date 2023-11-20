#include <iostream>
#include <list>
#include <queue>
#include "Node.h"
using namespace std;
class BinomialHeap
{
    list<Node *> heads;

    Node *mergeTrees(Node *a, Node *b)
    {
        if (a->getValue() > b->getValue())
        {
            Node *temp = a;
            a = b;
            b = temp;
        }
        b->parent = a;
        b->sibling = a->child;
        a->child = b;
        a->setDegree(a->getDegree() + 1);
        return a;
    }

    void adjustHeap()
    {
        if (this->heads.size() <= 1)
        {
            return;
        }
        auto it1 = this->heads.begin();
        auto it2 = this->heads.begin();
        auto it3 = this->heads.begin();
        if (this->heads.size() <= 2)
        {
            it2++;
            it3 = this->heads.end();
        }
        else
        {
            it2++;
            it3 = it2;
            it3++;
        }
        while (it1 != this->heads.end())
        {
            if (it2 == this->heads.end())
            {
                it1++;
            }
            else if ((*it1)->getDegree() < (*it2)->getDegree())
            {
                it1++;
                it2++;
                if (it3 != this->heads.end())
                {
                    it3++;
                }
            }
            else if (it3 != this->heads.end() && (*it1)->getDegree() == (*it2)->getDegree() && (*it2)->getDegree() == (*it3)->getDegree())
            {
                it1++;
                it2++;
                it3++;
            }
            else if ((*it1)->getDegree() == (*it2)->getDegree())
            {
                *it1 = mergeTrees(*it1, *it2);
                it2 = this->heads.erase(it2);
                if (it3 != this->heads.end())
                {
                    it3++;
                }
            }
        }
    }

public:
    void unionHeap(BinomialHeap *bh)
    {
        BinomialHeap *temp = new BinomialHeap();
        auto i = this->heads.begin();
        auto j = bh->heads.begin();
        while (i != this->heads.end() && j != bh->heads.end())
        {
            if ((*i)->getDegree() > (*j)->getDegree())
            {
                temp->heads.push_back(*j);
                j++;
            }
            else
            {
                temp->heads.push_back(*i);
                i++;
            }
        }
        while (i != this->heads.end())
        {
            temp->heads.push_back(*i);
            i++;
        }
        while (j != bh->heads.end())
        {
            temp->heads.push_back(*j);
            j++;
        }
        this->heads = temp->heads;
        adjustHeap();
    }

    void insert(int key)
    {
        Node *node = new Node(key);
        BinomialHeap *temp = new BinomialHeap();
        temp->heads.push_back(node);
        unionHeap(temp);
    }

    Node *findMin()
    {
        Node *temp;
        for (auto node : this->heads)
        {
            if ((node)->getValue() < temp->getValue())
            {
                temp = node;
            }
        }
        return temp;
    }

    Node *extractMin()
    {
        BinomialHeap *bh = new BinomialHeap();
        Node *temp = findMin();
        for (auto node : this->heads)
        {
            if (node != temp)
            {
                bh->heads.push_back(node);
            }
        }
        BinomialHeap *bh1 = new BinomialHeap();
        Node *temp1 = temp->child;
        Node *temp2;
        while (temp1)
        {
            temp2 = temp1;
            temp1 = temp1->sibling;
            temp2->sibling = NULL;
            bh1->heads.push_front(temp2);
        }
        this->heads = bh->heads;
        unionHeap(bh1);
        return temp;
    }

    void printHeap()
    {
        cout << "Printing Binomial Heap...\n";
        for (auto node : this->heads)
        {
            cout << "Binomial Tree, B" << node->getDegree();
            queue<Node *> q;
            int i = -1;
            q.push(node);
            node->setLevel(0);
            while (!q.empty())
            {
                Node *p = q.front();
                q.pop();
                if (p->getLevel() > i)
                {
                    cout << "\nLevel " << p->getLevel() << " : ";
                    i++;
                }
                cout << p->getValue() << " ";
                if (p->child)
                {
                    Node *temp = p->child;
                    while (temp)
                    {
                        q.push(temp);
                        temp->setLevel(p->getLevel() + 1);
                        temp = temp->sibling;
                    }
                }
            }
            cout << "\n";
        }
    }
};