#include <iostream>
#include "Graph1.h"
#include "Graph2.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Graph1 *g1;
    Graph2 *g2;
    int n, m, u, v, w, w1, w2;
    cin >> n >> m;
    g1 = new Graph1(n, m);
    g2 = new Graph2(n, m);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g1->addEdge(u - 1, v - 1, w);
        g1->addEdge(v - 1, u - 1, w);
        g2->addEdge(u - 1, v - 1, w);
        g2->addEdge(v - 1, u - 1, w);
    }
    cin >> w1 >> w2;
    // g->matrixMultiplication();
    g1->floydWarshall();
    int s, d;
    while (1)
    {
        cin >> s >> d;
        int ans = 0;
        if (s == -1 && d == -1)
        {
            break;
        }
        // s--;
        // d--;
        int path = g1->adj[s - 1][d - 1];
        if ((g1->apsp[s - 1][w1 - 1] == INT_MAX || g1->apsp[w2 - 1][d - 1] == INT_MAX) && (g1->apsp[s - 1][w2 - 1] == INT_MAX || g1->apsp[w1 - 1][d - 1] == INT_MAX))
        {
            cout << "No path from " << s << " to " << d << " through the Wall Street\n";
        }
        else if (g1->apsp[s - 1][w1 - 1] == INT_MAX || g1->apsp[w2 - 1][d - 1] == INT_MAX)
        {
            ans = g1->apsp[s - 1][w2 - 1] + path + g1->apsp[w1 - 1][d - 1];
            cout << "\nShortest Path Weight: " << ans << "\n";
            cout << "Path: ";
            ans = g2->dijkstra(s - 1, w2 - 1);
            g2->printPath(s - 1, w2 - 1);
            // cout << " -> " << w2 << " -> " << w1 << " -> ";
            cout << " -> ";
            ans = ans + g2->dijkstra(w1 - 1, d - 1);
            ans = ans + path;
            g2->printPath(w1 - 1, d - 1);
        }
        else if (g1->apsp[s - 1][w2 - 1] == INT_MAX || g1->apsp[w1 - 1][d - 1] == INT_MAX)
        {
            ans = g1->apsp[s - 1][w1 - 1] + path + g1->apsp[w2 - 1][d - 1];
            cout << "\nShortest Path Weight: " << ans << "\n";
            cout << "Path: ";
            ans = g2->dijkstra(s - 1, w1 - 1);
            g2->printPath(s - 1, w1 - 1);
            // cout << " -> " << w1 << " -> " << w2 << " -> ";
            cout << " -> ";
            ans = ans + g2->dijkstra(w2 - 1, d - 1);
            ans = ans + path;
            g2->printPath(w2 - 1, d - 1);
            // cout << "\nShortest Path Weight: " << ans << "\n";
        }
        else if ((g1->apsp[s - 1][w1 - 1] + path + g1->apsp[w2 - 1][d - 1]) > (g1->apsp[s - 1][w2 - 1] + path + g1->apsp[w1 - 1][d - 1]))
        {
            ans = g1->apsp[s - 1][w2 - 1] + path + g1->apsp[w1 - 1][d - 1];
            cout << "\nShortest Path Weight: " << ans << "\n";
            cout << "Path: ";
            ans = g2->dijkstra(s - 1, w2 - 1);
            ans = ans + path;
            g2->printPath(s - 1, w2 - 1);
            // cout << " -> " << w2 << " -> " << w1 << " -> ";
            cout << " -> ";
            ans = ans + g2->dijkstra(w1 - 1, d - 1);
            g2->printPath(w1 - 1, d - 1);
            // cout << "\nShortest Path Weight: " << ans << "\n";
        }
        else
        {
            ans = g1->apsp[s - 1][w1 - 1] + path + g1->apsp[w2 - 1][d - 1];
            cout << "\nShortest Path Weight: " << ans << "\n";
            cout << "Path: ";
            ans = g2->dijkstra(s - 1, w1 - 1);
            ans += path;
            g2->printPath(s - 1, w1 - 1);
            // cout << " -> " << w1 << " -> " << w2 << " -> ";
            cout << " -> ";
            ans += g2->dijkstra(w2 - 1, d - 1);
            g2->printPath(w2 - 1, d - 1);
            // cout << "\nShortest Path Weight: " << ans << "\n";
        }
        cout << "\n";
    }
}
