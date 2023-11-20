#include <iostream>
#include "graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("reverseDelete.txt", "w", stdout);
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
    cout << "Reverse Delete Algorithm:\n";
    double ans = g->kruskalMST();
    cout << "Total weight = " << ans << "\n";
    g->printMST();
    return 0;
}