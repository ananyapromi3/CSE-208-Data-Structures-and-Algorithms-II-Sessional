#include <iostream>
#include <vector>
#include <queue>
#define INF 1000000000
using namespace std;

class Graph
{
public:
    int vertex_count;
    vector<int> *adj;
    int **capacity;
    int **residualCapacity;
    bool *visited;
    int **path;

//public:
    int *parent;
    int *dist;
    Graph(int n)
    {
        vertex_count = n;
        adj = new vector<int>[n];
        parent = new int[n];
        visited = new bool[n];
        capacity = new int *[n];
        dist = new int[n];
        path =  new int*[n];
        residualCapacity = new int *[n];
        for (int i = 0; i < n; i++)
        {
            path[i] = new int[n];
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
//            path[i] = INF;
            parent[i] = -1;
            visited[i] = false;
            dist[i] = INF;
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
        dist[s] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v = 0; v < vertex_count; v++)
            {
                if (visited[v] == false && residualCapacity[u][v] > 0)
                {
                    visited[v] = true;
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
//                    if (v!=vertex_count-1 && u!=0)
//                    {
//                        cout << u << " " << v << " " << residualCapacity[u][v] << "\n";
//                    }
                    if (v == t)
                    {
//                        path[u] = min(path[u], residualCapacity[u][v]);
//                        cout << parent[u] << " " << u << " " << residualCapacity[u][v] << "\n";
                        path[parent[u]][u] = residualCapacity[u][v];
                        flag = true;
                        return flag;
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
//            path[i][j] = pathFlow;
            for (v = t; v != s; v = parent[v])
            {
                u = parent[v];
//                path[u][v] = pathFlow;
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
