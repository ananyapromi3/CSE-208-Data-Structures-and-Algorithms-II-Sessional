#include <iostream>
#include "Graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Graph *g;
    int n, m, u, v;
    cin >> n >> m;
    g = new Graph(n, m);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        g->addEdge(u, v);
    }
    g->DFS();
    if (g->isCyclic())
    {
        cout << -1 << "\n";
    }
    else
    {
        g->topologicalSorting();
    }
    return 0;
}