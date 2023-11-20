#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
class Graph // directed;
{
    int vertex_count;
    vector<pair<int, int> > *adj;
    int *dist;

public:
    int *parent;
    Graph(int n)
    {
        vertex_count = n;
        adj = new vector<pair<int, int> >[n];
        parent = new int[n];
        dist = new int[n];
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
};