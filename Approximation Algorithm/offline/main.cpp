#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "graph.h"
using namespace std;

Graph *create_random_graph(int n)
{
    srand(time(0));
    Graph *g;
    g = new Graph(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int w = rand() % 100 + 100;
            g->addEdge(i, j, w);
        }
    }
    return g;
}

int main()
{
    int testCase;
    cout << "Enter test case: ";
    cin >> testCase;
    int exact[testCase];
    int metric[testCase];
    for (int i = 0; i < testCase; i++)
    {
        Graph *g;
        g = create_random_graph(20);
        vector<int> v1;
        v1 = g->exact_tsp();
        exact[i] = g->calculate_tour_length(v1);
        vector<int> v2;
        v2 = g->eulerian_tour();
        metric[i] = g->calculate_tour_length(v2);
    }
    for (int i = 0; i < testCase; i++)
    {
        cout << "Test Case: " << i + 1 << "\tRatio: " << metric[i] * 1.0 / exact[i] << "\n";
    }
    return 0;
}