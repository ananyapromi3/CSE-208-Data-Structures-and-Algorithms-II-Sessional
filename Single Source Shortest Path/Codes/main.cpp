#include <iostream>
#include "graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Graph *g;
    int n, m, u, v, w, s, d, ans;
    cin >> n >> m;
    g = new Graph(n, m);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g->addEdge(u, v, w);
    }
    cin >> s >> d;
    cout << "Bellman Ford Algorithm:\n";
    ans = g->bellmanFord(s, d);
    if (g->negCycle())
    {
        cout << "Negative weight cycle present\n";
    }
    else
    {
        cout << "Total weight = " << ans << "\n";
        g->printPath(s, d);
    }
    cout << "\n";
    cout << "Dijkstra Algorithm:\n";
    ans = g->dijkstra(s, d);
    cout << "Total weight = " << ans << "\n";
    g->printPath(s, d);
    return 0;
}