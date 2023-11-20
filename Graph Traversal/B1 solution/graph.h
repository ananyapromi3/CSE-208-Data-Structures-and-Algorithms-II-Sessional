#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
enum colors
{
    white,
    black,
    gray
};
class Graph
{
public:
    int vertex_count, edge_count;
    map<int, vector<int> > adj;
    map<int, colors> color;
    map<int, int> parent;
    map<int, int> dist;

//public:
    Graph(int n)
    {
        vertex_count = n;
    }
    ~Graph()
    {
        init();
        adj.clear();
    }
    void init()
    {
        for (int i = 0; i < vertex_count; i++)
        {
            color[i] = white;
            parent[i] = i;
            dist[i] = INT_MAX;
        }
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int BFSvisit(int s)
    {
        init();
        int u, k, m = 0;
        int far = 0;
        color[s] = gray;
        dist[s] = 0;
        parent[s] = s;
        queue<int> q;
        q.push(s);
        while (!q.empty())
        {
            k = q.front();
            u = q.front();
            q.pop();
            for (auto v: adj[u])
            {
                if (color[v] == white)
                {
                    color[v] = gray;
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
            color[u] = black;
        }
        return k;
    }
};
