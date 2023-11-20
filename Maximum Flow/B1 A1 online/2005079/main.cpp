#include <iostream>
#include "Graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int m, n;
    cin >> m >> n;
    int x, y;
    cin >> x >> y;
    int v = 2 + x + y;
    Graph *g;
    g = new Graph(v);
    for (int i = 0; i < x; i++)
    {
        g->addFlow(0, i+1, n);
    }
    for (int i = 0; i < y; i++)
    {
        g->addFlow(i + 1 + x, v - 1, n);
    }
    int p, xx, yy;
    cin >> p;
    for (int i = 0; i < p; i++)
    {
        cin >> xx >> yy;
        g->addFlow(xx + 1, yy + 1 + x, m);
    }
    cout << g->Edmonds_Karp(0, v - 1) << "\n";
    for (int i = 1; i < x + 1; i++)
    {
        for (int j = x + 1; j < x + 1 + y; j++)
        {
//            cout << g->residualCapacity[i][j] << " ";
            if (g->path[i][j])
            {
                if (g->path[i][j] == n)
                {
                    g->path[i][j] = m;
                }
                cout << "(" << i - 1 << ", " << j - x - 1 << ") -> " << g->path[i][j] << " dances\n";
            }
        }
//        cout << "\n";
    }
//    for (int i = 0; i < y; i++)
//    {
//        cout << i << " " << g->path[i + x + 1] << "\n";
//    }
    return 0;
}
