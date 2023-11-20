#include <iostream>
#include "Graph.h"
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Graph *g;
    int n, m, u, v, w;
    cin >> n >> m;
    g = new Graph(n, m);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        g->addEdge(u - 1, v - 1, w);
    }
    g->matrixMultiplication();
    // g->floydWarshall();
    cout << "Shortest distance matrix:\n";
    g->printMatrix();
}

// 4 6
// 1 2 8
// 1 4 1
// 2 3 1
// 3 1 4
// 4 2 2
// 4 3 9

// 4 4
// 1 2 5
// 2 3 3
// 3 4 1
// 1 4 10