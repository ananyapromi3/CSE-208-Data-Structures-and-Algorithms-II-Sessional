#include <iostream>
#include <vector>
#include <queue>
#define INF 1000000000
using namespace std;

class Graph
{

    int vertex_count;
    vector<int> *adj;
    int **capacity;
    int **residualCapacity;
    bool *visited;

public:
    int *parent;
    Graph(int n)
    {
        vertex_count = n;
        adj = new vector<int>[n];
        parent = new int[n];
        visited = new bool[n];
        capacity = new int *[n];
        residualCapacity = new int *[n];
        for (int i = 0; i < n; i++)
        {
            capacity[i] = new int[n];
            residualCapacity[i] = new int[n];
        }
    }
    ~Graph()
    {
        for (int i = 0; i < vertex_count; i++)
        {
            adj[i].clear();
            delete[] capacity[i];
        }
        delete[] parent;
        delete[] capacity;
    }
    void init()
    {
        for (int i = 0; i < vertex_count; i++)
        {
            parent[i] = -1;
            visited[i] = false;
        }
    }
    void addFlow(int u, int v, int c)
    {
        adj[u].push_back(v);
        capacity[u][v] = c;
        capacity[v][u] = -c;
    }
    void updateFlow(int u, int v, int c)
    {
        capacity[u][v] = c;
        capacity[v][u] = -c;
    }
    bool BFS(int s, int t)
    {
        init();
        bool flag = false;
        queue<int> q;
        q.push(s);
        visited[s] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v = 0; v < vertex_count; v++)
            {
                if (visited[v] == false && residualCapacity[u][v] > 0)
                {
                    visited[v] = true;
                    parent[v] = u;
                    if (v == t)
                    {
                        flag = true;
                    }
                    q.push(v);
                }
            }
        }
        return flag;
    }
    int Edmonds_Karp(int s, int t)
    {
        int maxFlow = 0;
        int u, v;
        for (int i = 0; i < vertex_count; i++)
        {
            for (int j = 0; j < vertex_count; j++)
            {
                residualCapacity[i][j] = capacity[i][j];
            }
        }
        while (BFS(s, t))
        {
            int pathFlow = INF;
            for (v = t; v != s; v = parent[v])
            {
                u = parent[v];
                pathFlow = min(pathFlow, residualCapacity[u][v]);
            }
            maxFlow += pathFlow;
            for (v = t; v != s; v = parent[v])
            {
                u = parent[v];
                residualCapacity[u][v] -= pathFlow;
                residualCapacity[v][u] += pathFlow;
            }
        }
        return maxFlow;
    }
    bool isSaturated(int s)
    {
        for (auto v : adj[s])
        {
            if (residualCapacity[s][v] > 0)
            {
                return false;
            }
        }
        return true;
    }
};