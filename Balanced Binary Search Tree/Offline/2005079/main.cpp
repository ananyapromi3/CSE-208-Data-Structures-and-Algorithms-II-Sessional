#include "AVLtree.h"
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;
int main()
{
    FILE *fpin = freopen("in.txt", "r", stdin);
    FILE *fpout1 = freopen("out_avl.txt", "w", stdout);
    BST *bst;
    bst = new BST();
    char command;
    int key;
    double insert_time = 0.0, delete_time = 0.0, search_time = 0.0, traversal_time = 0.0;
    time_t start, end;
    while (cin >> command)
    {
        if (command == 'F')
        {
            cin >> key;
            start = clock();
            bool ans = bst->find(key);
            end = clock();
            if (!ans)
            {
                cout << "not found\n";
            }
            else
            {
                cout << "found\n";
            }
            search_time += double(end - start) / double(CLOCKS_PER_SEC);
        }
        else if (command == 'I')
        {
            cin >> key;
            start = clock();
            bst->insertVal(key);
            end = clock();
            insert_time += double(end - start) / double(CLOCKS_PER_SEC);
            bst->displayBST();
        }
        else if (command == 'D')
        {
            cin >> key;
            start = clock();
            bst->deleteVal(key);
            end = clock();
            delete_time += double(end - start) / double(CLOCKS_PER_SEC);
            bst->displayBST();
        }
        else if (command == 'T')
        {
            start = clock();
            bst->inorderTraversal();
            end = clock();
            traversal_time += double(end - start) / double(CLOCKS_PER_SEC);
        }
    }
    fclose(fpout1);
    FILE *fpout2 = freopen("report_avl.txt", "w", stdout);
    cout << "operation time(ms)\n";
    cout << "insert " << insert_time << "\n";
    cout << "delete " << delete_time << "\n";
    cout << "search " << search_time << "\n";
    cout << "trav " << traversal_time << "\n";
    cout << "total " << insert_time + delete_time + search_time + traversal_time << "\n";
    fclose(fpout2);
    return 0;
}