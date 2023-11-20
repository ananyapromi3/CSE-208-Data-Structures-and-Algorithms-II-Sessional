#include "BinomialHeap.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    BinomialHeap *bh = new BinomialHeap();
    char command;
    while (cin >> command)
    {
        if (command == 'I')
        {
            int val;
            cin >> val;
            bh->insert(val);
        }
        if (command == 'P')
        {
            bh->printHeap();
        }
        if (command == 'F')
        {
            cout << "Find-Min returned " << bh->findMin()->getValue() << "\n";
        }
        if (command == 'E')
        {
            cout << "Extract-Min returned " << bh->extractMin()->getValue() << "\n";
        }
        if (command == 'U')
        {
            BinomialHeap *temp = new BinomialHeap();
            vector<int> v;
            string str;
            getline(cin, str);
            stringstream ss(str);
            for (int i = 0; ss >> i;)
            {
                v.push_back(i);
            }
            for (auto u : v)
            {
                temp->insert(u);
            }
            bh->unionHeap(temp);
        }
    }
    return 0;
}