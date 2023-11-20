#include <iostream>
#include "graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Graph *g;
    int n, m, u, v, w, ans;
    cin >> n >> m;
    g = new Graph(n, m);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g->addEdge(u, v, w);
    }
    cout << "Dijkstra Algorithm:\n";
    ans = g->dijkstra(0, n-1);
    for (int i = 0; i < n; i++)
    {
        cout << i << ": " << g->countBest(i) << "\n"; 
    }
    return 0;
}