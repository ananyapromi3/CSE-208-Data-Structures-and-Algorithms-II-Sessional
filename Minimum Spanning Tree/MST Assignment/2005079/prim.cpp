#include <iostream>
#include "graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("prim.txt", "w", stdout);
    Graph *g;
    int n, m, u, v;
    double w;
    cin >> n >> m;
    g = new Graph(n, m);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g->addEdge(u, v, w);
    }
    cout << "Prim-Jarnik Algorithm:\n";
    int root = g->primMST();
    cout << "Total weight = " << g->totalWeightPrim() << "\n";
    cout << "Root node = " << root << "\n";
    g->printPrim();
    return 0;
}