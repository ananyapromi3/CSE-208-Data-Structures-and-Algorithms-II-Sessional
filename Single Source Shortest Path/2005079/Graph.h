#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
class Graph // directed;
{
    int vertex_count, edge_count;
    vector<pair<int, int> > *adj;
    int *parent;
    int *dist;
    bool isNegCycle;

public:
    Graph(int n, int m)
    {
        vertex_count = n;
        edge_count = m;
        adj = new vector<pair<int, int> >[n];
        parent = new int[n];
        dist = new int[n];
        isNegCycle = false;
    }
    ~Graph()
    {
        init();
        for (int i = 0; i < vertex_count; i++)
        {
            adj[i].clear();
        }
        delete[] adj;
        delete[] parent;
        delete[] dist;
    }
    void init()
    {
        for (int i = 0; i < vertex_count; i++)
        {
            parent[i] = -1;
            dist[i] = INT_MAX;
        }
        isNegCycle = false;
    }
    void addEdge(int u, int v, double w)
    {
        adj[u].push_back(make_pair(v, w));
    }
    bool relax(int u, int v, int w)
    {
        if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
        {
            dist[v] = dist[u] + w;
            parent[v] = u;
            return true;
        }
        return false;
    }
    int dijkstra(int src, int dest)
    {
        init();
        priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > q;
        dist[src] = 0;
        q.push(make_pair(dist[src], src));
        while (!q.empty())
        {
            int u = q.top().second;
            q.pop();
            for (auto p : adj[u])
            {
                int v = p.first;
                int w = abs(p.second);
                if (relax(u, v, w))
                {
                    q.push(make_pair(dist[v], v));
                }
            }
        }
        return dist[dest];
    }
    int bellmanFord(int src, int dest)
    {
        init();
        dist[src] = 0;
        for (int k = 0; k < vertex_count; k++)
        {
            for (int i = 0; i < vertex_count; i++)
            {
                for (auto p: adj[i])
                {
                    int u = i;
                    int v = p.first;
                    int w = p.second;
                    relax(u, v, w);
                }
            }
        }
        for (int i = 0; i < vertex_count; i++)
        {
            for (auto p: adj[i])
            {
                int u = i;
                int v = p.first;
                int w = p.second;
                if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
                {
                    isNegCycle = true;
                }
            }
        }
        return dist[dest];
    }
    void printPath(int s, int d)
    {
        stack<int> path;
        int i = d;
        while(parent[i] != -1)
        {
            path.push(i);
            i = parent[i];
        }
        if (i != s) 
        {
            cout << "No path found\n";
        }
        else 
        {
            cout << s;
            while (!path.empty())
            {
                int v = path.top();
                path.pop();
                cout << " -> " << v;
            }
            cout << "\n";
        }
    }
    bool negCycle()
    {
        return isNegCycle;
    }
};