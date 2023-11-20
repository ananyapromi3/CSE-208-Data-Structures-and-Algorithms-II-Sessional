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
    int vertex_count, edge_count;
    map<int, vector<int> > adj;
    vector<pair<int, int> > treeEdge;
    vector<pair<int, int> > backEdge;
    vector<pair<int, int> > crossEdge;
    vector<pair<int, int> > forwardEdge;
    map<int, colors> color;
    map<int, int> start_time;
    map<int, int> end_time;
    map<int, int> parent;
    map<int, int> dist;
    map<int, int> partition;
    stack<int> topo_sort;
    int time;
    bool cyclic;
    bool bipartite;

public:
    Graph(int n, int m)
    {
        vertex_count = n;
        edge_count = m;
    }
    ~Graph()
    {
        init();
        adj.clear();
    }
    void init()
    {
        time = 0;
        for (int i = 0; i < vertex_count; i++)
        {
            color[i] = white;
            parent[i] = i;
            start_time[i] = 0;
            end_time[i] = 0;
            dist[i] = INT_MAX;
            partition[i] = 0;
        }
        while (!topo_sort.empty())
        {
            topo_sort.pop();
        }
        backEdge.clear();
        crossEdge.clear();
        treeEdge.clear();
        forwardEdge.clear();
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }
    void BFS()
    {
        init();
        for (int i = 0; i < vertex_count; i++)
        {
            if (color[i] == white)
            {
                BFSvisit(i);
            }
        }
    }
    void BFSvisit(int s)
    {
        color[s] = gray;
        dist[s] = 0;
        parent[s] = s;
        queue<int> q;
        q.push(s);
        partition[s] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto v: adj[u])
            {
                if (partition[v] == partition[u])
                {
                    bipartite = false;
                }
                if (color[v] == white)
                {
                    if (partition[v] != partition[u])
                    {
                        partition[v] = 3 - partition[u];
                    }
                    color[v] = gray;
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    treeEdge.push_back(make_pair(u, v));
                    q.push(v);
                }
                else if (color[v] == gray)
                {
                    crossEdge.push_back(make_pair(u, v));
                }
                else
                {
                    backEdge.push_back(make_pair(u, v));
                }
            }
            color[u] = black;
        }
    }
    void DFS()
    {
        init();
        for (int i = 0; i < vertex_count; i++)
        {
            if (color[i] == white)
            {
                DFSvisit(i);
            }
        }
    }
    void DFSvisit(int u)
    {
        start_time[u] = ++time;
        color[u] = gray;
        for (auto v : adj[u])
        {
            if (color[v] == white)
            {
                parent[v] = u;
                treeEdge.push_back(make_pair(u, v));
                DFSvisit(v);
            }
            else if (color[v] == gray)
            {
                backEdge.push_back(make_pair(u, v));
                cyclic = true;
            }
            else
            {
                if (start_time[u] < start_time[v])
                {
                    forwardEdge.push_back(make_pair(u, v));
                }
                else
                {
                    crossEdge.push_back(make_pair(u, v));
                }
            }
        }
        color[u] = black;
        end_time[u] = ++time;
        topo_sort.push(u);
    }
    bool isCyclic()
    {
        cyclic = false;
        DFS();
        return cyclic;
    }
    bool isBipartite()
    {
        bipartite = true;
        BFS();
        return bipartite;
    }
    void print()
    {
        cout << "Tree edges:\n";
        for (int i = 0; i < vertex_count; i++)
        {
            if (parent[i] != i)
            {
                cout << parent[i] << "->" << i << "\n";
            }
        }
        cout << "\n";
        cout << "Back edges:\n";
        for (auto p : backEdge)
        {
            cout << p.first << "->" << p.second << "\n";
        }
        cout << "\n";
        cout << "Forward edges:\n";
        for (auto p : forwardEdge)
        {
            cout << p.first << "->" << p.second << "\n";
        }
        cout << "\n";
        cout << "Cross edges:\n";
        for (auto p : crossEdge)
        {
            cout << p.first << "->" << p.second << "\n";
        }
        cout << "\n";
    }
    void topologicalSorting()
    {
        while (!topo_sort.empty())
        {
            cout << topo_sort.top() << " ";
            topo_sort.pop();
        }
        cout << "\n";
    }
};