#include <iostream>
using namespace std;
class Graph // directed;
{
    int vertex_count, edge_count;
    // int **adj;
    // int **apsp;
    int adj[100][100];
    int apsp[100][100];

public:
    Graph(int n, int m)
    {
        vertex_count = n;
        edge_count = m;
        // int **adj = new int *[n];
        // int **apsp = new int *[n];
        // for (int i = 0; i < n; i++)
        // {
        //     adj[i] = new int[n];
        //     apsp[i] = new int[n];
        // }
        for (int i = 0; i < vertex_count; i++)
        {
            for (int j = 0; j < vertex_count; j++)
            {
                adj[i][j] = INT_MAX;
            }
        }
        for (int i = 0; i < vertex_count; i++)
        {
            adj[i][i] = 0;
        }
    }
    ~Graph()
    {
        // for (int i = 0; i < vertex_count; i++)
        // {
        //     delete[] adj[i];
        //     delete[] apsp[i];
        // }
        // delete[] adj;
        // delete[] apsp;
    }
    void firstItr()
    {
        for (int i = 0; i < vertex_count; i++)
        {
            for (int j = 0; j < vertex_count; j++)
            {
                apsp[i][j] = adj[i][j];
            }
        }
    }
    void addEdge(int u, int v, double w)
    {
        adj[u][v] = w;
    }
    void matrixMultiplication()
    {
        firstItr();
        for (int t = 1; t < vertex_count - 1; t++)
        {
            for (int i = 0; i < vertex_count; i++)
            {
                for (int j = 0; j < vertex_count; j++)
                {
                    for (int k = 0; k < vertex_count; k++)
                    {
                        if (apsp[i][k] != INT_MAX && adj[k][j] != INT_MAX)
                        {
                            apsp[i][j] = min(apsp[i][k] + adj[k][j], apsp[i][j]);
                        }
                    }
                }
            }
        }
    }
    void floydWarshall()
    {
        firstItr();
        for (int i = 0; i < vertex_count; i++)
        {
            for (int j = 0; j < vertex_count; j++)
            {
                for (int k = 0; k < vertex_count; k++)
                {
                    if (apsp[i][k] != INT_MAX && apsp[k][j] != INT_MAX)
                    {
                        apsp[i][j] = min(apsp[i][k] + apsp[k][j], apsp[i][j]);
                    }
                }
            }
        }
    }
    void printMatrix()
    {
        for (int i = 0; i < vertex_count; i++)
        {
            for (int j = 0; j < vertex_count; j++)
            {
                if (apsp[i][j] == INT_MAX)
                {
                    cout << "INF ";
                }
                else
                {
                    cout << apsp[i][j] << " ";
                }
            }
            cout << "\n";
        }
    }
};