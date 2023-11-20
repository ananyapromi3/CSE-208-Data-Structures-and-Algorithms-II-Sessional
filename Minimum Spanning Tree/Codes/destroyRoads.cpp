#include <iostream>
#include "graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("destroyRoads.txt", "w", stdout);
    Graph *gMen, *gWomen;
    int n, m, u, v;
    int flag;
    cin >> n >> m;
    gMen = new Graph(n, m);
    gWomen = new Graph(n, m);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> flag;
        u--;
        v--;
        if (flag == 3)
        {
            gMen->addEdge(u, v, 1.0);
            gWomen->addEdge(u, v, 1.0);
        }
        else if (flag == 1)
        {
            gMen->addEdge(u, v, 2.0);
        }
        else if (flag == 2)
        {
            gWomen->addEdge(u, v, 2.0);
        }
    }
    if (!gMen->isConnected() || !gWomen->isConnected())
    {
        cout << -1 << "\n";
    }
    else
    {
        gMen->primMST();
        gWomen->primMST();
        set<pair<int, int> > edge;
        for (auto e : gMen->mstEdge)
        {
            edge.insert(e);
        }
        for (auto e : gWomen->mstEdge)
        {
            edge.insert(e);
        }
        cout << m - edge.size() << "\n";
    }
    return 0;
}