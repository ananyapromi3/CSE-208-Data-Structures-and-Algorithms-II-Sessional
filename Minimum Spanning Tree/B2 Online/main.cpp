#include <iostream>
#include "graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Graph *g;
    int n, m, u, v;
    double w, q;
    cin >> n >> m >> q;
    g = new Graph(n, m);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g->addEdge(u, v, min(w, q));
    }
    int root = g->primMST();
    cout << "Total weight = " << g->totalWeightPrim() << "\n";
    // g->printMST();
    return 0;
}