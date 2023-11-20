#include <iostream>
#include "graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Graph *g;
    int n, m, u, v, w, s, ans;
    cin >> n >> m;
    g = new Graph(n, m);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g->addEdge(u, v, w);
    }
    cin >> s;
    int minDist = INT_MAX;
    int d;
    for (int i = 0; i < n; i++)
    {
        if (i != s)
        {
            int go = g->dijkstra(s, i);
            int back = g->dijkstra(i, s);
            if (go != INT_MAX && back != INT_MAX && go + back < minDist)
            {
                minDist = go + back;
                d = i;
            }
        }
    }
    cout << "Minimum total time: " << minDist << "\n\nPaths:\n";
    int goTime = g->dijkstra(s, d);
    g->printPath(s, d);
    cout << "(time: " << goTime << ")\n";
    int backTime = g->dijkstra(d, s);
    g->printPath(d, s);
    cout << "(time: " << backTime << ")\n";
    return 0;
}