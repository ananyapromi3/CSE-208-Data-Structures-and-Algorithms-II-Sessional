#include <iostream>
#include "graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Graph *g;
    int n, m, u, v, s, d;
    double w, ans;
    cin >> n >> m;
    g = new Graph(n, m);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g->addEdge(u, v, w);
    }
    cin >> s >> d;
    ans = g->dijkstra(s, d);
    cout << "Most reliable path score: " << ans << "\n";
    g->printPath(s, d);
    return 0;
}