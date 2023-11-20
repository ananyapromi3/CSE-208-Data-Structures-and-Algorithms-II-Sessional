#include <iostream>
#include "Graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Graph *g;
    int n, m, u, v;
    cin >> n;
    g = new Graph(n);
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        g->addEdge(u, v);
    }
    int l1 = g->BFSvisit(0);
    cout << l1 << "\n";
    int l2 = g->BFSvisit(l1);
    cout << l2 << "\n";
    int i = l2;
    int k = n;
    while (k--)
    {
        cout << i << " ";
        i = g->parent[i];
        if (i == l1)
        {
            cout << i << " ";
            break;
        }
    }
    return 0;
}
